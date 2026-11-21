#include "application.h"

#include "double3.h"
#include "inputManager.h"
#include "shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Application::Application() {
    std::cout << "Initialising..." << std::endl;
    if (!glfwInit()) {
        std::cout << "Could not init GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window.reset(glfwCreateWindow(800, 600, "Loop Subdivision", nullptr, nullptr),
                   DestroyglfwWin{});
    if (!m_window) {
        std::cout << "No window initialised." << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window.get());

    if (glewInit() != GLEW_OK) {
        std::cout << "Could not init GLEW" << std::endl;
        return;
    }
    InputManager::get().init(m_window);
    InputManager::get().registerKey(GLFW_KEY_ESCAPE, [&](int action, int mods) {
        if (action == GLFW_PRESS) {
            glfwSetWindowShouldClose(m_window.get(), GLFW_TRUE);
        }
    });
}

void Application::run() {
    m_lastFrameTime = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(m_window.get())) {
        // 1. Calculate deltaTime in seconds
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - m_lastFrameTime;
        m_lastFrameTime = currentFrameTime;
        glfwPollEvents();

        update(deltaTime);
        draw();

        glfwSwapBuffers(m_window.get());
    }
}

void Application::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Application::update(float DT) {
    smath::double3 a(1, 0, 0);
    smath::double3 y(1, 0, 0);
    static bool doOnce = false;
    if (!doOnce) {
        std::cout << a << std::endl;
        std::cout << smath::crossProduct(a, y, smath::explain) << std::endl;
        std::cout << smath::dotProduct(a, y, smath::explain) << std::endl;
        doOnce = true;
    }
}

Application::~Application() {
    // Explicitly destroy the window BEFORE glfwTerminate()
    m_window.reset();
    glfwTerminate();
}