#ifndef __gl_shader_h__
#define __gl_shader_h__

#include <GL/glew.h>

#include "log.hpp"
#include "gshader.hpp"

namespace trimana_core::renderer::opengl
{
    /**
     * @brief The shader_type enum class represents the types of shaders.
     */
    enum class shader_type
    {
        none = -1,                    /**< No shader type */
        vertex = GL_VERTEX_SHADER,    /**< Vertex shader type */
        fragment = GL_FRAGMENT_SHADER /**< Fragment shader type */
    };

    /**
     * @class gl_shader
     * @brief Represents an OpenGL shader.
     *
     * The `gl_shader` class inherits from the `shader` base class and provides an implementation for OpenGL shaders.
     * It allows creating, binding, and setting uniforms for vertex and fragment shaders.
     */
    class gl_shader : public shader
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

}

#endif // __gl_shader_h__