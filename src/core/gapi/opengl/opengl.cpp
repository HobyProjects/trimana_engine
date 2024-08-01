#include "opengl.hpp"

namespace core::gapi::opengl
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GETTING GL INFO /////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    gl_info::gl_info()
    {
        m_gl_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
        m_gl_vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
        m_gl_renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
        m_glsl_version = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));

        char GL_MAJOR = m_gl_version[0];
        char GL_MINOR = m_gl_version[2];
        char GL_PATCH = m_gl_version[4];

        std::stringstream ss;
        ss << "#version " << GL_MAJOR << GL_MINOR << GL_PATCH << " core";
        m_glsl_version = ss.str();
    }

    void gl_info::show() const
    {
        TRIMANA_CORE_INFO("--------------------------------------------------------");
        TRIMANA_CORE_INFO("OpenGL Info:");
        TRIMANA_CORE_INFO("     Version:        {0}", m_gl_version);
        TRIMANA_CORE_INFO("     Vendor:         {0}", m_gl_vendor);
        TRIMANA_CORE_INFO("     Renderer:       {0}", m_gl_renderer);
        TRIMANA_CORE_INFO("     GLSL Version:   {0}", m_glsl_version);
        TRIMANA_CORE_INFO("--------------------------------------------------------");
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GL CONTEXT ///////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

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

        m_info = std::make_unique<gl_info>();
        m_info->show();
    }

    void gl_context::swap_buffers()
    {
        glfwSwapBuffers(m_window);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GL VERTEX BUFFER /////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    gl_vertex_buffer::gl_vertex_buffer(float* vertices, size_t size,gl_draw_type type) 
    {
        gl_call(glGenBuffers(1, &m_renderer_id));
        gl_call(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
        gl_call(glBufferData(GL_ARRAY_BUFFER, size, vertices, static_cast<GLenum>(type)));
    }

    gl_vertex_buffer::~gl_vertex_buffer() 
    {
        gl_call(glDeleteBuffers(1, &m_renderer_id));
    }

    void gl_vertex_buffer::bind() const 
    {
        gl_call(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    }

    void gl_vertex_buffer::unbind() const 
    {
        gl_call(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GL INDEX BUFFER //////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    gl_index_buffer::gl_index_buffer(unsigned int* indices, size_t count, gl_draw_type type) 
    {
        gl_call(glGenBuffers(1, &m_renderer_id));
        gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
        gl_call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(size_t), indices, static_cast<GLenum>(type)));
        m_count = count;
    }

    gl_index_buffer::~gl_index_buffer() 
    {
        gl_call(glDeleteBuffers(1, &m_renderer_id));
    }

    void gl_index_buffer::bind() const 
    {
        gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    }

    void gl_index_buffer::unbind() const 
    {
        gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GL VERTEX ARRAY //////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    gl_vertex_array::gl_vertex_array() 
    {
        gl_call(glGenVertexArrays(1, &m_renderer_id));
    }

    gl_vertex_array::~gl_vertex_array() 
    {
        gl_call(glDeleteVertexArrays(1, &m_renderer_id));
    }

    void gl_vertex_array::bind() const 
    {
        gl_call(glBindVertexArray(m_renderer_id));
    }

    void gl_vertex_array::unbind() const 
    {
        gl_call(glBindVertexArray(0));
    }

    void gl_vertex_array::emplace_vertex_buffer(const sptr<core::renderer::vertex_buffers>& vertex_buffer) 
    {
        vertex_buffer->bind();

        const auto& layout = vertex_buffer->get_layout();
        const auto& elements = layout.get_elements();

        size_t index = 0;

        for (const auto& element : elements) 
        {
            gl_call(glEnableVertexAttribArray(index));
            gl_call(glVertexAttribPointer(index, element.component_type, gl_data_type::gl_float, element.normalized, layout.get_stride(), (const void*)element.offset));
            index++;
        }

        m_vertex_buffers.emplace_back(vertex_buffer);
    }

    void gl_vertex_array::set_index_buffer(const sptr<core::renderer::index_buffers>& index_buffer) 
    {
        index_buffer->bind();
        m_index_buffer = index_buffer;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GL SHADER /////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

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

    bool gl_shader::set_uniform_mat4(const std::string &name, const glm::mat4 &value)
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

    bool gl_shader::set_uniform_mat3(const std::string &name, const glm::mat3 &value)
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

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GL RENDERER ///////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    void gl_api_base::set_clear_color(const glm::vec4& color) 
    {
        gl_call(glClearColor(color.r, color.g, color.b, color.a));
    }

    void gl_api_base::clear() 
    {
        gl_call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void gl_api_base::draw_indexed(const sptr<core::renderer::vertex_array>& vertex_array) 
    {
        auto& index_buffer = vertex_array->get_index_buffer();
        gl_call(glDrawElements(GL_TRIANGLES, index_buffer->get_count(), GL_UNSIGNED_INT, nullptr));
    }


}