#include "shader.h"

#include <fstream>
#include <iostream>
namespace {
// Maybe move to a utilities funtion later.
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void checkShaderCompiled(GLuint shader) {
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        GLint len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

        if (len > 0) {
            std::string log(len, '\0');
            glGetShaderInfoLog(shader, len, nullptr, log.data());
            glDeleteShader(shader);
            throw std::runtime_error("Shader compilation failed:\n" + std::string(log));
        }
    }
}

void checkLinkErrors(GLuint program) {
    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        GLint len = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
        if (len > 0) {
            std::string log(len, '\0');
            glGetProgramInfoLog(program, len, nullptr, log.data());
            glDeleteProgram(program);
            throw std::runtime_error("Shader linking failed:\n" + std::string(log));
        }
    }
}

void compileShader(GLenum type, const std::string& source) {
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    // compile the shader
    glCompileShader(shader);
    checkShaderCompiled(shader) return shader;
}

} // namespace

void Shader::buildFromSource(const std::string& vertexCode, const std::string& fragmentCode) {
    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    m_id = glCreateProgram();

    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);

    glLinkProgram(m_id);
    checkLinkErrors(m_id);

    // Shaders are linked into the program and no longer needed separately
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    buildFromSource(readFile(vertexPath), readFile(fragmentPath));
}

Shader::~Shader() {
    if (m_id != 0) {
        glDeleteProgram(m_id);
    }
}

void Shader::use() const { glUseProgram(m_id); }
