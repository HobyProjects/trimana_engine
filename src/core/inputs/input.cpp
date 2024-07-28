#include "input.hpp"

namespace core::inputs
{
    std::weak_ptr<core::windows::window> input::m_window;

    void input::target_window(const std::shared_ptr<core::windows::window> window)
    {
        m_window = window;
    }

    bool input::is_key_pressed(int32_t key_code)
    {
        TRIMANA_ASSERT(m_window.expired() == true, "Window is not set for input.");
        if(auto window = m_window.lock())
        {
            auto state = glfwGetKey(window->get_native_window(), key_code);
            return state == GLFW_PRESS || state == GLFW_REPEAT;
        }

        return false;
    }

    bool input::is_mouse_button_pressed(int32_t button)
    {
        TRIMANA_ASSERT(m_window.expired() == true, "Window is not set for input.");
        if(auto window = m_window.lock())
        {
            auto state = glfwGetMouseButton(window->get_native_window(), button);
            return state == GLFW_PRESS;
        }

        return false;
    }

    std::pair<float, float> input::mouse_pos()
    {
        TRIMANA_ASSERT(m_window.expired() == true, "Window is not set for input.");
        if(auto window = m_window.lock())
        {
            double x, y;
            glfwGetCursorPos(window->get_native_window(), &x, &y);
            return std::pair<float, float>(static_cast<float>(x), static_cast<float>(y));
        }

        return std::pair<float, float>(0.0f, 0.0f);
    }

    float input::mouse_pos_x()
    {
        TRIMANA_ASSERT(m_window.expired() == true, "Window is not set for input.");
        if(auto window = m_window.lock())
        {
            auto[x, y] = mouse_pos();
            return x;
        }

        return 0.0f;
    }

    float input::mouse_pos_y()
    {
        TRIMANA_ASSERT(m_window.expired() == true, "Window is not set for input.");
        if(auto window = m_window.lock())
        {
            auto[x, y] = mouse_pos();
            return y;
        }

        return 0.0f;
    }
}