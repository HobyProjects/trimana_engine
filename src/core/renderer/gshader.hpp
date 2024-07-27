#ifndef __gshader_h__
#define __gshader_h__

#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "platform_detection.hpp"

namespace trimana_core::renderer
{
    /**
     * @brief The shader class is an abstract base class for shaders.
     */
    class TRIMANA_API shader
    {
    public:
        shader() = default;
        virtual ~shader() = default;

        /**
         * @brief Binds the shader.
         */
        virtual void bind() const = 0;

        /**
         * @brief Unbinds the shader.
         */
        virtual void unbind() const = 0;

        /**
         * @brief Sets a uniform integer value in the shader.
         * @param name The name of the uniform variable.
         * @param value The integer value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_1i(const std::string &name, int value) = 0;

        /**
         * @brief Sets a uniform unsigned integer value in the shader.
         * @param name The name of the uniform variable.
         * @param value The unsigned integer value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_1ui(const std::string &name, unsigned int value) = 0;

        /**
         * @brief Sets a uniform float value in the shader.
         * @param name The name of the uniform variable.
         * @param value The float value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_1f(const std::string &name, float value) = 0;

        /**
         * @brief Sets a uniform 2D vector value in the shader.
         * @param name The name of the uniform variable.
         * @param value The 2D vector value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_2f(const std::string &name, const glm::vec2 &value) = 0;

        /**
         * @brief Sets a uniform 3D vector value in the shader.
         * @param name The name of the uniform variable.
         * @param value The 3D vector value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_3f(const std::string &name, const glm::vec3 &value) = 0;

        /**
         * @brief Sets a uniform 4D vector value in the shader.
         * @param name The name of the uniform variable.
         * @param value The 4D vector value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_4f(const std::string &name, const glm::vec4 &value) = 0;

        /**
         * @brief Sets a uniform 4x4 matrix value in the shader.
         * @param name The name of the uniform variable.
         * @param value The 4x4 matrix value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_mat4f(const std::string &name, const glm::mat4 &value) = 0;

        /**
         * @brief Sets a uniform 3x3 matrix value in the shader.
         * @param name The name of the uniform variable.
         * @param value The 3x3 matrix value to set.
         * @return True if the uniform was set successfully, false otherwise.
         */
        virtual bool set_uniform_mat3f(const std::string &name, const glm::mat3 &value) = 0;
    };

    /**
     * @brief Creates a shader object with the given vertex and fragment shader source code.
     * @param vertex_shader The source code of the vertex shader.
     * @param fragment_shader The source code of the fragment shader.
     * @return A pointer to the created shader object.
     */
    TRIMANA_API shader *create_shader(const std::string &vertex_shader, const std::string &fragment_shader);
}

#endif // __gshader_h__