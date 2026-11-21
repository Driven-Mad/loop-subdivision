#include <unordered_map>
#include <functional>
#include <vector>

class InputManager {
public:
    using KeyCallback = std::function<void(int action, int mods)>;

    // Global access point
    static InputManager& get() {
        static InputManager instance;
        return instance;
    }

    void init(const std::shared_ptr<GLFWwindow>& window)
    {
        m_window = window;
        if (window) {
            glfwSetKeyCallback(window.get(), glfwKeyCallback);
        }
    }

    // Prevent copying or moving
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    // Register a callback for a specific key
    void registerKey(int key, KeyCallback callback) {
        m_bindings[key].push_back(std::move(callback));
    }

private:
    InputManager() = default;
    std::unordered_map<int, std::vector<KeyCallback>> m_bindings;
    std::weak_ptr<GLFWwindow> m_window;

    static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto& instance = get();
        auto it = instance.m_bindings.find(key);
        if (it != instance.m_bindings.end()) {
            for (const auto& callback : it->second) {
                callback(action, mods);
            }
        }
    }
};
