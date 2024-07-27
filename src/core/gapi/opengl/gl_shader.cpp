#include "gl_shader.hpp"
#include "assert.hpp"
#include <vector>

namespace trimana_core::renderer::opengl
{
    gl_shader::gl_shader(const std::string &vertex_shader, const std::string &fragment_shader)
    {
        m_program_id = glCreateProgram();
        if(!m_program_id)
        {
            TRIMANA_CORE_ERROR("Failed to create shader program");
            return;
        }

        std::string vertex_shader_code = import_shader(vertex_shader);
        std::string fragment_shader_code = import_shader(fragment_shader);

        uint32_t vertex_shader_id = compile_shader(m_program_id, vertex_shader_code, shader_type::vertex);
        uint32_t fragment_shader_id = compile_shader(m_program_id, fragment_shader_code, shader_type::fragment);

        glAttachShader(m_program_id, vertex_shader_id);
        glAttachShader(m_program_id, fragment_shader_id);

        int result = 0;
        glLinkProgram(m_program_id);
        glGetProgramiv(m_program_id, GL_LINK_STATUS, &result);

        if(!result)
        {
            char linker_error_message[1024];
            glGetProgramInfoLog(m_program_id, sizeof(linker_error_message), nullptr, linker_error_message);
            TRIMANA_CORE_ERROR("Failed to link shader program >> {0}", linker_error_message);
            return;
        }
        
        glValidateProgram(m_program_id);
        glGetProgramiv(m_program_id, GL_VALIDATE_STATUS, &result);

        if(!result)
        {
            char validate_error_message[1024];
            glGetProgramInfoLog(m_program_id, sizeof(validate_error_message), nullptr, validate_error_message);
            TRIMANA_CORE_ERROR("Failed to validate shader program >> {0}", validate_error_message);
            return;
        }

        glDetachShader(m_program_id, vertex_shader_id);
        glDeleteShader(vertex_shader_id);

        glDetachShader(m_program_id, fragment_shader_id);
        glDeleteShader(fragment_shader_id);
    }

    gl_shader::~gl_shader()
    {
        glDeleteProgram(m_program_id);
    }

    void gl_shader::bind() const
    {
        glUseProgram(m_program_id);
    }

    void gl_shader::unbind() const
    {
        glUseProgram(0);
    }

    bool gl_shader::set_uniform_1i(const std::string &name, int value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniform1i(uniform_location, value);
        return true;
    }

    bool gl_shader::set_uniform_1ui(const std::string &name, unsigned int value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniform1ui(uniform_location, value);
        return true;
    }

    bool gl_shader::set_uniform_1f(const std::string &name, float value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniform1f(uniform_location, value);
        return true;
    }

    bool gl_shader::set_uniform_2f(const std::string &name, const glm::vec2 &value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniform2fv(uniform_location, 1, glm::value_ptr(value));
        return true;
    }

    bool gl_shader::set_uniform_3f(const std::string &name, const glm::vec3 &value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniform3fv(uniform_location, 1, glm::value_ptr(value));
        return true;
    }

    bool gl_shader::set_uniform_4f(const std::string &name, const glm::vec4 &value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniform4fv(uniform_location, 1, glm::value_ptr(value));
        return true;
    }

    bool gl_shader::set_uniform_mat4f(const std::string &name, const glm::mat4 &value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value));
        return true;
    }

    bool gl_shader::set_uniform_mat3f(const std::string &name, const glm::mat3 &value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        glUniformMatrix3fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value));
        return true;
    }

    uint32_t gl_shader::get_uniform_location(const std::string &name) const
    {
        return uniform_validator(name);
    }

    uint32_t gl_shader::uniform_validator(const std::string &name) const
    {
        uint32_t uniform_location = glGetUniformLocation(m_program_id, name.c_str());
        if(uniform_location == -1)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return -1;
        }

        return uniform_location;
    }

    uint32_t gl_shader::compile_shader(uint32_t &program_id, const std::string &shader_code, shader_type type) const
    {
        uint32_t shader_id = glCreateShader(static_cast<GLenum>(type));
        const char *shader_code_c_str = shader_code.c_str();

        glShaderSource(shader_id, 1, &shader_code_c_str, nullptr);
        glCompileShader(shader_id);

        int result = 0;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

        if(result == GL_FALSE)
        {
            int message_length = 0;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &message_length);

            std::vector<char> compile_error_message(message_length);
            glGetShaderInfoLog(shader_id, message_length, &message_length, &compile_error_message[0]);
            TRIMANA_CORE_ERROR("Failed to compile shader >> {0}", compile_error_message.data());
            return -1;
        }

        return shader_id;
    }
    
    std::string gl_shader::import_shader(const std::string &file_path) const
    {
        std::string fileContent{" "};
        std::fstream shaderFile;

        shaderFile.open(file_path.c_str(), std::ios::in);
        if (!shaderFile.is_open())
        {
            TRIMANA_CORE_CRITICAL("Unbale to open file: {0}", file_path.c_str());
            return fileContent;
        }
        else
        {
            std::string lines{" "};
            while (!shaderFile.eof())
            {
                std::getline(shaderFile, lines);
                fileContent.append(lines + "\n");
            }

            shaderFile.close();
        }

        return fileContent;
    }
}
