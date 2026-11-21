#pragma once
#include <GL/glew.h> // Required for include order.
#include <GLFW/glfw3.h>
#include <memory>

class Application {
  public:
    Application();
    // Prevent copying the application
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();
    ///\brief draw function to draw to screen all objects etc.
    void draw();
    ///\brief update function to update any movement etc. for objects
    void update(float DT);

    ~Application();

  private:
    struct DestroyglfwWin {
        void operator()(GLFWwindow* ptr) const {
            if (ptr) {

                glfwDestroyWindow(ptr);
            }
        }
    };
    std::shared_ptr<GLFWwindow> m_window;
    float m_lastFrameTime = 0.0f;
};