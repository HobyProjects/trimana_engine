#include "gl_context.hpp"
#include "assert.hpp"

namespace trimana_core::renderer::opengl
{
    gl_context::gl_context(GLFWwindow *window) : m_window(window)
    {
        TRIMANA_ASSERT(window == nullptr, "Window is null");
    }

    void gl_context::init()
    {
        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1);
        
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
        m_gl_info = std::make_unique<gl_info>();

        m_gl_info->show_gl_info();
    }

    void gl_context::swap_buffers()
    {
        glfwSwapBuffers(m_window);
    }
}