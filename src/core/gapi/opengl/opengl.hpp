#ifndef __opengl_h__
#define __opengl_h__

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


#include <memory>
#include <string>
#include <sstream>

#include "log.hpp"
#include "assert.hpp"

#include "renderer.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// OPENGL ERROR HANDLING ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline GLenum glCheckErrors(const char* file, int line) 
{
    GLenum errorCode  {NULL};
    const char* error {nullptr};

    while ((errorCode = glGetError()) != GL_NO_ERROR) 
    {
            switch (errorCode) 
            {
                case GL_INVALID_ENUM:                     error = TRIMANA_STRINGIFY_MACRO(GL_INVALID_ENUM); break;
                case GL_INVALID_VALUE:                    error = TRIMANA_STRINGIFY_MACRO(GL_INVALID_VALUE); break;
                case GL_INVALID_OPERATION:                error = TRIMANA_STRINGIFY_MACRO(GL_INVALID_OPERATION); break;
                case GL_STACK_OVERFLOW:                   error = TRIMANA_STRINGIFY_MACRO(GL_STACK_OVERFLOW); break;
                case GL_STACK_UNDERFLOW:                  error = TRIMANA_STRINGIFY_MACRO(GL_STACK_UNDERFLOW); break;
                case GL_OUT_OF_MEMORY:                    error = TRIMANA_STRINGIFY_MACRO(GL_OUT_OF_MEMORY); break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:    error = TRIMANA_STRINGIFY_MACRO(GL_INVALID_FRAMEBUFFER_OPERATION); break;
                case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: error = TRIMANA_STRINGIFY_MACRO(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS); break;
            }
    }

    if (error != nullptr)
        TRIMANA_CORE_CRITICAL("OpenGL Error: {0} in  FILE : {1} | LINE : {2}", error, file, line);

    return errorCode;
}

#define gl_call(GL_FUNC) \
  GL_FUNC;                    \
  glCheckErrors(__FILE__, __LINE__)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace core::gapi::opengl 
{
    /**
     * @brief The OpenGL information class that contains information about the OpenGL context.
     */
    class TRIMANA_API gl_info
    {
        public:
            /**
             * @brief Constructs a gl_info object.
             */
            gl_info();

            /**
             * @brief Default destructor for the gl_info class.
             */
            ~gl_info() = default;

            /**
             * @brief Gets the OpenGL version.
             * @return The OpenGL version.
             */
            const std::string &gl_version() const { return m_gl_version; }

            /**
             * @brief Gets the OpenGL vendor.
             * @return The OpenGL vendor.
             */
            const std::string &gl_vendor() const { return m_gl_vendor; }

            /**
             * @brief Gets the OpenGL renderer.
             * @return The OpenGL renderer.
             */
            const std::string &gl_renderer() const { return m_gl_renderer; }

            /**
             * @brief Gets the GLSL version.
             * @return The GLSL version.
             */
            const std::string &glsl_version() const { return m_glsl_version; }

            /**
             * @brief Shows the OpenGL information.
             */
            void show() const;

        private:
            std::string m_gl_version;       /**< The OpenGL version. */
            std::string m_gl_vendor;        /**< The OpenGL vendor. */
            std::string m_gl_renderer;      /**< The OpenGL renderer. */
            std::string m_glsl_version;     /**< The GLSL version. */
    };

    /**
     * @brief The OpenGL context class that inherits from the context class.
     * 
     * This class represents an OpenGL context used for rendering graphics.
     */
    class TRIMANA_API gl_context : public renderer::context
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
        std::shared_ptr<gl_info> get_info() const { return m_info; }

    private:
        GLFWwindow* m_window{ nullptr }; /**< The GLFW window associated with the OpenGL context. */
        std::shared_ptr<gl_info> m_info{nullptr}; /**< The OpenGL information object that contains information about the OpenGL context. */
    };

    /**
     * @brief Enumeration representing the draw type of a vertex buffer object.
     */
    enum class gl_draw_type
    {
        draw_static   = GL_STATIC_DRAW,  /**< Static draw type */
        draw_dynamic  = GL_DYNAMIC_DRAW /**< Dynamic draw type */
    };

    /**
     * @brief Enumeration representing the data type of a vertex buffer object.
     */
    enum gl_data_type : unsigned int 
    {
        gl_none   = NULL,                 /**< No data type */
        gl_float  = GL_FLOAT,             /**< Float data type */
        gl_uint   = GL_UNSIGNED_INT,      /**< Unsigned integer data type */
        gl_byte   = GL_BYTE,              /**< Byte data type */
        gl_ubyte  = GL_UNSIGNED_BYTE,     /**< Unsigned byte data type */
        gl_int    = GL_INT                /**< Integer data type */
    };

    /**
     * @brief The OpenGL implementation of a vertex buffer.
     *
     * This class represents a vertex buffer in OpenGL.
     * It inherits from the base class vertex_buffers.
     */
    class TRIMANA_API gl_vertex_buffer : public renderer::vertex_buffers 
    {
        public:
            /**
             * @brief Constructs a gl_vertex_buffer object.
             *
             * @param vertices A pointer to the vertex data.
             * @param size The size of the vertex data in bytes.
             * @param type The draw type of the vertex buffer.
             */
            gl_vertex_buffer(float *vertices, size_t size, gl_draw_type type);

            /**
             * @brief Destroys the gl_vertex_buffer object.
             */
            virtual ~gl_vertex_buffer();

            /**
             * @brief Binds the vertex buffer.
             *
             * This function binds the vertex buffer to the OpenGL context.
             */
            void bind() const override;

            /**
             * @brief Unbinds the vertex buffer.
             *
             * This function unbinds the vertex buffer from the OpenGL context.
             */
            void unbind() const override;

            /**
             * @brief Gets the laෆyout of the vertex buffer.
             * @return The layout of the vertex buffer.
             */
            virtual const renderer::buffer_layout &get_layout() const override { return m_layout; }

            /**
             * @brief Sets the layout of the vertex buffer.
             * @param layout The layout of the vertex buffer object.
             */
            virtual void set_layout(const renderer::buffer_layout &layout) override { m_layout = layout; }

        private:
            unsigned int m_renderer_id;       /**< The ID of the OpenGL renderer. */
            renderer::buffer_layout m_layout; /**< The layout of the vertex buffer. */
    };

    /**
     * @brief The OpenGL implementation of an index buffer.
     *
     * This class represents an index buffer in OpenGL.
     * It inherits from the base class index_buffer.
     */
    class TRIMANA_API gl_index_buffer : public renderer::index_buffers 
    {
        public:
            /**
             * @brief Constructs a gl_index_buffer object.
             *
             * @param indices A pointer to the index data.
             * @param size The size of the index data in bytes.
             */
            gl_index_buffer(unsigned int *indices, size_t count, gl_draw_type type);

            /**
             * @brief Destroys the gl_index_buffer object.
             */
            virtual ~gl_index_buffer();

            /**
             * @brief Binds the index buffer.
             *
             * This function binds the index buffer to the OpenGL context.
             */
            void bind() const override;

            /**
             * @brief Unbinds the index buffer.
             *
             * This function unbinds the index buffer from the OpenGL context.
             */
            void unbind() const override;

            /**
             * @brief Gets the count of indices in the index buffer.
             * @return The count of indices in the index buffer.
             */
            size_t get_count() const override { return m_count; }

        private:
            size_t m_count;             /**< The count of indices in the index buffer. */
            unsigned int m_renderer_id; /**< The ID of the OpenGL renderer. */
    };

     /**
     * @brief The gl_vertex_array class represents a vertex array object in OpenGL.
     *
     * This class inherits from the vertex_array base class and provides an implementation
     * for OpenGL-specific functionality.
     */
    class TRIMANA_API gl_vertex_array : public renderer::vertex_array
    {
        public:
            /**
             * @brief Constructs a new gl_vertex_array object.
             */
            gl_vertex_array();

            /**
             * @brief Destroys the gl_vertex_array object.
             */
            virtual ~gl_vertex_array();

            /**
             * @brief Binds the vertex array object.
             */
            virtual void bind() const override;

            /**
             * @brief Unbinds the vertex array object.
             */
            virtual void unbind() const override;

            /**
             * @brief Adds a vertex buffer to the vertex array.
             *
             * @param vertex_buffer The vertex buffer to add.
             */
            virtual void emplace_vertex_buffer(const std::shared_ptr<renderer::vertex_buffers> &vertex_buffer) override;

            /**
             * @brief Sets the index buffer for the vertex array.
             *
             * @param index_buffer The index buffer to set.
             */
            virtual void set_index_buffer(const std::shared_ptr<renderer::index_buffers> &index_buffer) override;

            /**
             * @brief Returns the vector of vertex buffers associated with the vertex array.
             *
             * @return The vector of vertex buffers.
             */
            const std::vector<std::shared_ptr<renderer::vertex_buffers>> &get_vertex_buffers() const override { return m_vertex_buffers; }

            /**
             * @brief Returns the index buffer associated with the vertex array.
             *
             * @return The index buffer.
             */
            const std::shared_ptr<renderer::index_buffers> &get_index_buffer() const override { return m_index_buffer; }

        private:
            uint32_t m_renderer_id{NULL};                                            // The ID of the renderer
            std::vector<std::shared_ptr<renderer::vertex_buffers>> m_vertex_buffers; // Vector of vertex buffers
            std::shared_ptr<renderer::index_buffers> m_index_buffer;                 // Index buffers
    };

    /**
     * @brief The shader_type enum class represents the types of shaders.
     */
    enum class shader_type
    {
        none        = NULL,                     /**< No shader type */
        vertex      = GL_VERTEX_SHADER,         /**< Vertex shader type */
        fragment    = GL_FRAGMENT_SHADER        /**< Fragment shader type */
    };

    /**
     * @class gl_shader
     * @brief Represents an OpenGL shader.
     *
     * The `gl_shader` class inherits from the `shader` base class and provides an implementation for OpenGL shaders.
     * It allows creating, binding, and setting uniforms for vertex and fragment shaders.
     */
    class TRIMANA_API gl_shader : public renderer::shader
    {
        public:
            /**
             * @brief Constructs a `gl_shader` object with the specified vertex and fragment shader source code.
             *
             * @param vertex_shader The source code of the vertex shader.
             * @param fragment_shader The source code of the fragment shader.
             */
            gl_shader(const std::string &vertex_shader, const std::string &fragment_shader);

            /**
             * @brief Destroys the `gl_shader` object.
             */
            virtual ~gl_shader();

            /**
             * @brief Binds the shader for rendering.
             */
            virtual void bind() const override;

            /**
             * @brief Unbinds the shader.
             */
            virtual void unbind() const override;

            /**
             * @brief Sets a 1-dimensional integer uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_1i(const std::string &name, int value) override;

            /**
             * @brief Sets a 1-dimensional unsigned integer uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_1ui(const std::string &name, unsigned int value) override;

            /**
             * @brief Sets a 1-dimensional floating-point uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_1f(const std::string &name, float value) override;

            /**
             * @brief Sets a 2-dimensional floating-point uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_2f(const std::string &name, const glm::vec2 &value) override;

            /**
             * @brief Sets a 3-dimensional floating-point uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_3f(const std::string &name, const glm::vec3 &value) override;

            /**
             * @brief Sets a 4-dimensional floating-point uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_4f(const std::string &name, const glm::vec4 &value) override;

            /**
             * @brief Sets a 4x4 matrix uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_mat4f(const std::string &name, const glm::mat4 &value) override;

            /**
             * @brief Sets a 3x3 matrix uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @param value The value to set.
             * @return `true` if the uniform variable was found and set successfully, `false` otherwise.
             */
            virtual bool set_uniform_mat3f(const std::string &name, const glm::mat3 &value) override;

            /**
             * @brief Returns the ID of the shader program.
             *
             * @return The ID of the shader program.
             */
            uint32_t get_program_id() const;

            /**
             * @brief Returns the location of a uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @return The location of the uniform variable.
             */
            uint32_t get_uniform_location(const std::string &name) const;

        private:
            /**
             * @brief Validates a uniform variable in the shader.
             *
             * @param name The name of the uniform variable.
             * @return The location of the uniform variable.
             */
            uint32_t uniform_validator(const std::string &name) const;

            /**
             * @brief Compiles a shader and returns its ID.
             *
             * @param program_id The ID of the shader program.
             * @param shader_code The source code of the shader.
             * @param type The type of the shader.
             * @return The ID of the compiled shader.
             */
            uint32_t compile_shader(uint32_t &program_id, const std::string &shader_code, shader_type type) const;

            /**
             * @brief Imports the source code of a shader from a file.
             *
             * @param file_path The path to the shader file.
             * @return The source code of the shader.
             */
            std::string import_shader(const std::string &file_path) const;

        private:
            uint32_t m_program_id{NULL};
    };

     /**
     * @brief The OpenGL implementation of the renderer API.
     */
    class TRIMANA_API gl_api_base : public renderer::renderer_api
    {
    public:
        /**
         * @brief Default constructor for the gl_api_base class.
         */
        gl_api_base() = default;

        /**
         * @brief Default destructor for the gl_api_base class.
         */
        ~gl_api_base() = default;

        /**
         * @brief Draws the indexed vertex array.
         * 
         * @param vertex_array The shared pointer to the vertex array.
         */
        void draw_indexed(const std::shared_ptr<renderer::vertex_array>& vertex_array) override;

        /**
         * @brief Sets the clear color for the renderer.
         * 
         * @param color The color to set as the clear color.
         */
        void set_clear_color(const glm::vec4& color) override;

        /**
         * @brief Clears the renderer.
         */
        void clear() override;
    };

} 

#endif // __opengl_h__