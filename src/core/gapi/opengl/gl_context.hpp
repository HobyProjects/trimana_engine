#ifndef __gl_context_h__
#define __gl_context_h__


/*---------------------------------------[INCLUDING GLFW AND GLEW WITHOUT ANY CONFLICT]----------------------------------------*/

/**
 * Include the GLEW header file.
 *
 * The GLEW library is a cross-platform open-source C/C++ extension library
 * designed to provide support for the OpenGL API on computers that don't
 * natively support it.
 *
 * By including this header file, we ensure that the GLEW library is included
 * and that we can use its functions and constants in our code.
 */
#include <GL/glew.h>

/**
 * GLFW_INCLUDE_NONE is special macro
 * that helps us void colletions between
 * glfw.h and glew.h headers. This macro
 * is used to prevent GLFW header from
 * including OpenGL headers. This is
 * needed because GLEW library also
 * includes OpenGL headers and there can
 * be conflicts between them.
 *
 * 
 * This macro is used to prevent GLFW
 * header from including OpenGL headers
 * only when GLEW is included. When GLEW
 * is not included, GLFW header will
 * include OpenGL headers as usual.
 */
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#ifndef _glfw3_h_
#include <GLFW/glfw3.h>
#endif

// Stop APIENTRY redefinition warnings
#ifdef APIENTRY
#undef APIENTRY
#endif

/*---------------------------------------------------------------------------------------------------------------------------*/

#include "context.hpp"
#include "gl_info.hpp"

namespace trimana_core::renderer::opengl
{
    /**
     * @brief The OpenGL context class that inherits from the graphics_context class.
     * 
     * This class represents an OpenGL context used for rendering graphics.
     */
    class TRIMANA_API gl_context : public graphics_context
    {
    public:
        /**
         * @brief Constructs a gl_context object with the specified GLFW window.
         * 
         * @param window The GLFW window associated with the OpenGL context.
         */
        gl_context(GLFWwindow* window);

        /**
         * @brief Default destructor for the gl_context class.
         */
        virtual ~gl_context() = default;

        /**
         * @brief Initializes the OpenGL context.
         * 
         * This function initializes the OpenGL context and sets up any necessary configurations.
         */
        virtual void init() override;

        /**
         * @brief Swaps the front and back buffers of the OpenGL context.
         * 
         * This function swaps the front and back buffers of the OpenGL context, displaying the rendered image on the screen.
         */
        virtual void swap_buffers() override;

        /**
         * @brief Gets the OpenGL information object associated with the OpenGL context.
         * 
         * @return A shared pointer to the OpenGL information object.
         */
        std::shared_ptr<gl_info> get_gl_info() const { return m_gl_info; }

    private:
        GLFWwindow* m_window{ nullptr }; /**< The GLFW window associated with the OpenGL context. */
        std::shared_ptr<gl_info> m_gl_info{nullptr}; /**< The OpenGL information object that contains information about the OpenGL context. */
    };
}


#endif // __gl_context_h__