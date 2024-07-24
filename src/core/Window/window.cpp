#include "window.hpp"

namespace trimana_core::window
{
    /**
     * @brief Creates a window with a title.
     * @param title The title of the window.
     */
    window::window(const std::string &title)
    {
        // Initialize the loggers with the log::init_loggers() function.
        // This function returns a boolean indicating whether the loggers were
        // successfully initialized or not.
        bool log_init = loggers::log::init_loggers();

        // Assert that the loggers were successfully initialized. If not,
        // raise a critical error message with the log::get_core_logger()
        // function.
        TRIMANA_ASSERT(log_init == false, "Failed to initialize loggers");

        // Initialize GLFW. This function returns a boolean indicating whether
        // GLFW was successfully initialized or not. If not, raise a critical
        // error message with the log::get_core_logger() function and return
        // from the function.
        if(!glfwInit())
        {
            // Raise a critical error message with the log::get_core_logger()
            // function.
            TRIMANA_CORE_CRITICAL("Failed to initialize GLFW");

            // Return from the function.
            return;
        }

        // Raise an info message with the log::get_core_logger() function.
        TRIMANA_CORE_INFO("GLFW initialized");

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

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
            glfwMakeContextCurrent(m_window); //[TODO]:This should BE move a differnt class when we workinh with opengl or anyother api
            // Set the swap interval to 1
            glfwSwapInterval(1);

            // Set the window's attributes
            m_attributes.is_active = true;
            m_attributes.is_focused = true;
            m_attributes.is_vsync_enabled = true;

            // Enable experimental support for GLEW (required for core profile contexts)
            glewExperimental = true;
            
            // Initialize GLEW
            // GLEW (OpenGL Extension Wrangler Library) is a cross-platform open-source
            // C/C++ extension loading library designed to provide efficient run-time
            // mechanisms for determining which OpenGL extensions are supported on the
            // target platform.
            // Here, we are initializing GLEW to ensure that we can use the OpenGL
            // extensions that our application requires.
            // If 'glewInit()' returns 'GLEW_OK', then GLEW has been successfully
            // initialized and we can proceed with using the required OpenGL extensions.
            // If 'glewInit()' returns any other value, then GLEW initialization has
            // failed and we should print an error message.
            GLenum status = glewInit();
            TRIMANA_ASSERT(status != GLEW_OK, "Failed to initialize GLEW");

            return;
        }

        // Print an error message if the window could not be created
        TRIMANA_CORE_ERROR("Failed to create window");
    }

    /**
     * @brief Destructor for the window class.
     *
     * This destructor is responsible for destroying the window and terminating the GLFW context.
     * It first checks if the window is not nullptr, and if so, it destroys the window using glfwDestroyWindow.
     * Then, it terminates the GLFW context using glfwTerminate.
     */
    window::~window()
    {
        if(m_window != nullptr)
        {
            // Destroy the window using glfwDestroyWindow
            glfwDestroyWindow(m_window);
        }

        // Terminate the GLFW context using glfwTerminate
        glfwTerminate();      
    }

} // namespace trimana_core::window
