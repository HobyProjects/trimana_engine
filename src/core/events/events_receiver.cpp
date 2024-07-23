#include "events_receiver.hpp"

namespace trimana_core::events
{
    /**
     * The static callback function for all events.
     */
    events_callback_func events_receiver::m_events_callback;

    /**
     * The weak pointer to the window.
     */
    std::weak_ptr<trimana_core::window::window> events_receiver::m_window;


    /**
     * Polls for events and processes them.
     *
     * This function is responsible for polling for events and processing
     * them. It retrieves the events from the platform-specific event system
     * and forwards them to the event handler for processing.
     *
     * The function does not block, so it can be used in a loop to poll for
     * events and process them. This is useful for applications that need to
     * continuously update the window contents without waiting for events.
     */
    void events_receiver::poll_events()
    {
        glfwWaitEvents();
    }

    /**
     * Sets the event callback function for the window.
     *
     * This function sets the event callback function for the given window. The
     * callback function is responsible for handling the window events. This
     * function also updates the window pointer and replaces the previous
     * callback function.
     *
     * @param window The shared pointer to the window object for which the
     * events are being handled. This parameter is used to update the window
     * pointer and to ensure that events are only handled for the correct window.
     * @param callback The callback function that will be called when events
     * occur. This function should take a reference to an event object as a parameter
     * and perform any necessary actions based on the event type.
     */
    void events_receiver::set_eventts_callback(std::shared_ptr<window::window> window, const events_callback_func &callback)
    {
        m_events_callback = callback;
        m_window = window;

        // Set the window close callback
        glfwSetWindowCloseCallback(window->get_native_window(), [](GLFWwindow *window) {
            if(!m_window.expired())
            {
                window_close_event window_close;
                m_events_callback(window_close);
            }
        });

        // Set the window size callback
        glfwSetWindowSizeCallback(window->get_native_window(), [](GLFWwindow *window, int width, int height) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                window_ptr->get_sizes().width = width;
                window_ptr->get_sizes().height = height;
                window_resize_event window_resize(width, height);
                m_events_callback(window_resize);
            }
        });

        // Set the window position callback
        glfwSetWindowPosCallback(window->get_native_window(), [](GLFWwindow *window, int xpos, int ypos) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                window_ptr->get_position().posx = xpos;
                window_ptr->get_position().posy = ypos;
                window_pos_change_event window_move(xpos, ypos);
                m_events_callback(window_move);
            }
        });

        // Set the window focus callback
        glfwSetWindowFocusCallback(window->get_native_window(), [](GLFWwindow *window, int focused) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                if(focused)
                {
                    window_focus_gain_event window_focus;
                    m_events_callback(window_focus);
                }
                else
                {
                    window_focus_lost_event window_unfocus;
                    m_events_callback(window_unfocus);
                }
            }
        });

        // Set the window maximize callback
        glfwSetWindowMaximizeCallback(window->get_native_window(), [](GLFWwindow *window, int maximized) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                window_ptr->get_attributes().state = window::window_status::maximized;
                window_maximize_event window_maximize;
                m_events_callback(window_maximize);
            }
        });

        // Set the window minimize callback
        glfwSetWindowIconifyCallback(window->get_native_window(), [](GLFWwindow *window, int iconified) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                window_ptr->get_attributes().state = window::window_status::minimized;
                window_minimize_event window_minimize;
                m_events_callback(window_minimize);
            }
        });

        // Set the framebuffer size callback
        glfwSetFramebufferSizeCallback(window->get_native_window(), [](GLFWwindow *window, int width, int height) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                window_ptr->get_framebuffer_sizes().width = width;
                window_ptr->get_framebuffer_sizes().height = height;
                window_frame_resize_event window_resize(width, height);
                m_events_callback(window_resize);
            }
        });

        // Set the cursor enter callback
        glfwSetCursorEnterCallback(window->get_native_window(), [](GLFWwindow* window, int entered) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                if(entered)
                {
                    mouse_cursor_enter_event cursor_enter;
                    m_events_callback(cursor_enter);
                }
                else
                {
                    mouse_cursor_leave_event cursor_leave;
                    m_events_callback(cursor_leave);
                }
            }
        });

        // Set the cursor position callback
        glfwSetCursorPosCallback(window->get_native_window(), [](GLFWwindow *window, double xpos, double ypos) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                mouse_cursorpos_change_event cursor_position(xpos, ypos);
                m_events_callback(cursor_position);
            }
        });

        // Set the mouse button callback
        glfwSetMouseButtonCallback(window->get_native_window(), [](GLFWwindow *window, int button, int action, int mods) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                if(action == GLFW_PRESS)
                {
                    mouse_button_press_event mouse_press(button);
                    m_events_callback(mouse_press);
                }
                else if(action == GLFW_RELEASE)
                {
                    mouse_button_release_event mouse_release(button);
                    m_events_callback(mouse_release);
                }
            }
        });

        // Set the scroll callback
        glfwSetScrollCallback(window->get_native_window(), [](GLFWwindow *window, double xoffset, double yoffset) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                mouse_wheel_scroll_event mouse_scroll(xoffset, yoffset);
                m_events_callback(mouse_scroll);
            }
        });

        // Set the key callback
        glfwSetKeyCallback(window->get_native_window(), [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                if(action == GLFW_PRESS)
                {
                    keyboard_keypress_event key_press(key);
                    m_events_callback(key_press);
                }
                else if(action == GLFW_RELEASE)
                {
                    keyboard_keyrelease_event key_release(key);
                    m_events_callback(key_release);
                }
                else if(action == GLFW_REPEAT)
                {
                    keyboard_keyrepeate_event key_repeate(key);
                    m_events_callback(key_repeate);
                }
            }
        });

        // Set the character callback
        glfwSetCharCallback(window->get_native_window(), [](GLFWwindow *window, unsigned int codepoint) {
            if(!m_window.expired())
            {
                auto window_ptr = m_window.lock();
                keyboard_keychar_event key_char(codepoint);
                m_events_callback(key_char);
            }
        });
    }
}