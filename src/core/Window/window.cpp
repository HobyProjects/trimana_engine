#include "window.hpp"

namespace trimana_core::window
{
    /**
     * @brief Creates a window with a title.
     * @param title The title of the window.
     */
    window::window(const std::string &title)
    {
        // Get the video mode of the primary monitor
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        if (mode != nullptr)
        {
            // Set the fixed sizes of the window
            m_fixed_sizes.max_w = mode->width;
            m_fixed_sizes.max_h = mode->height;
            m_fixed_sizes.min_w = 1024;
            m_fixed_sizes.min_h = 720;

            // Set the video mode of the window
            m_vid_modes.red_color_bit = mode->redBits;
            m_vid_modes.green_color_bit = mode->greenBits;
            m_vid_modes.blue_color_bit = mode->blueBits;
            m_vid_modes.refresh_rate = mode->refreshRate;
        }
        else
        {
            // Set default values if the video mode of the primary monitor could not be retrieved
            TRIMANA_CORE_WARN("Failed to get monitor video mode");
            m_fixed_sizes.max_w = NULL;
            m_fixed_sizes.max_h = NULL;
            m_fixed_sizes.min_w = 800;
            m_fixed_sizes.min_h = 600;
            m_vid_modes.red_color_bit = 8;
            m_vid_modes.green_color_bit = 8;
            m_vid_modes.blue_color_bit = 8;
            m_vid_modes.refresh_rate = 8;
        }

        // Set window hints
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        // This hint is ignored for full screen windows
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FOCUS_ON_SHOW);
        // Set the number of bits for each color component
        glfwWindowHint(GLFW_RED_BITS, m_vid_modes.red_color_bit);
        glfwWindowHint(GLFW_GREEN_BITS, m_vid_modes.green_color_bit);
        glfwWindowHint(GLFW_BLUE_BITS, m_vid_modes.blue_color_bit);
        // Since GLFWvidmode does not have alpha, we set it to red_color_bit for now
        glfwWindowHint(GLFW_ALPHA_BITS,  m_vid_modes.red_color_bit); 

        // Set the number of bits for the depth and stencil buffers
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        // Enable the stencil buffer
        glfwWindowHint(GLFW_STENCIL_BITS, GLFW_TRUE);


        //[TODO]:Check this after we get opengl version info 
        // // Get the major and minor version of the OpenGL context
        // int major, minor;
        // glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR, &major);
        // glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR, &minor);
        // // Set the major and minor version of the OpenGL context
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

        // Set the OpenGL profile to the core profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Enable forward compatibility for OpenGL
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

        // Create the window
        m_attributes.title = title;
        m_window = glfwCreateWindow(m_fixed_sizes.min_w, m_fixed_sizes.min_h, m_attributes.title.c_str(), nullptr, nullptr);
        if (m_window != nullptr)
        {
            TRIMANA_CORE_INFO("Window created");

            // Set the window size limits
            glfwSetWindowSizeLimits(m_window, m_fixed_sizes.min_w, m_fixed_sizes.min_h, GLFW_DONT_CARE, GLFW_DONT_CARE);
            // Get the size of the window's framebuffer
            glfwGetFramebufferSize(m_window, &m_window_framebuffer.width, &m_window_framebuffer.height);
            // Make the window the current context
            glfwMakeContextCurrent(m_window);
            // Set the swap interval to 1
            glfwSwapInterval(1);

            // Set the window's attributes
            m_attributes.is_active = true;
            m_attributes.is_focused = true;
            m_attributes.is_vsync_enabled = true;
            return;
        }

        // Print an error message if the window could not be created
        TRIMANA_CORE_ERROR("Failed to create window");
    }

    window::~window()
    {
        if(m_window != nullptr)
            glfwDestroyWindow(m_window);
    }

} // namespace trimana_core::window
