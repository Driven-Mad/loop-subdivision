#pragma once
#include <GL/glew.h> // Required for include order.
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace DefaultShaders {

inline constexpr const char* BASIC_VERT = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
)";

inline constexpr const char* BASIC_FRAG = R"(
#version 330 core
out vec4 FragColor;

uniform vec3 uColor;

void main() {
    FragColor = vec4(uColor, 1.0);
}
)";

} // namespace DefaultShaders

class Shader {
  public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    static Shader fromSource(const std::string& vertexCode, const std::string& fragmentCode) {
        Shader shader;
        shader.buildFromSource(vertexCode, fragmentCode);
        return shader;
    }
    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setVec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

  private:
    Shader();
    void buildFromSource(const std::string& vertexCode, const std::string& fragmentCode);

    GLint getUniformLocation(const std::string& name) const {
        auto it = m_uniformCache.find(name);
        if (it != m_uniformCache.end()) return it->second;

        GLint location = glGetUniformLocation(m_id, name.c_str());
        m_uniformCache[name] = location;
        return location;
    }

    GLuint m_id = 0;
    mutable std::unordered_map<std::string, GLint> m_uniformCache;
};