#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
    ////////////////////////////////////// GL SHADER /////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    gl_shader::gl_shader(const std::string & path)
    {
        std::string source = import_shader(path);
        auto shader_sources = pre_process(source);
        compile_shader(shader_sources);
    }

    gl_shader::~gl_shader()
    {
        gl_call(glDeleteProgram(m_program_id));
    }

    void gl_shader::bind() const
    {
        gl_call(glUseProgram(m_program_id));
    }

    void gl_shader::unbind() const
    {
        gl_call(glUseProgram(0));
    }

    bool gl_shader::set_uniform_1i(const std::string &name, int value)
    {
        uint32_t uniform_location = uniform_validator(name);
        if(uniform_location < 0)
        {
            TRIMANA_CORE_ERROR("Failed to find uniform >> {0}", name);
            return false;
        }

        gl_call(glUniform1i(uniform_location, value));
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

        gl_call(glUniform1ui(uniform_location, value));
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

        gl_call(glUniform1f(uniform_location, value));
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

        gl_call(glUniform2fv(uniform_location, 1, glm::value_ptr(value)));
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

        gl_call(glUniform3fv(uniform_location, 1, glm::value_ptr(value)));
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

        gl_call(glUniform4fv(uniform_location, 1, glm::value_ptr(value)));
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

        gl_call(glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value)));
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

        gl_call(glUniformMatrix3fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value)));
        return true;
    }

    uint32_t gl_shader::get_program_id() const
    {
        return m_program_id;
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

    void gl_shader::compile_shader(std::unordered_map<GLenum, std::string> shaders)
    {
        uint32_t shader_program = glCreateProgram();
        if(shader_program == GL_FALSE)
        {
            TRIMANA_CORE_ERROR("Failed to create shader program");
            return;
        }

        std::vector<uint32_t> shader_ids{};
        shader_ids.reserve(shaders.size());

        for(auto& type_n_shaders : shaders)
        {
            GLenum type = type_n_shaders.first;
            const std::string &shader_code = type_n_shaders.second;

            uint32_t shader_id = glCreateShader(static_cast<GLenum>(type));
            const char *shader_code_c_str = shader_code.c_str();

            gl_call(glShaderSource(shader_id, 1, &shader_code_c_str, nullptr));
            gl_call(glCompileShader(shader_id));

            int result = 0;
            gl_call(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result));

            if(result == GL_FALSE)
            {
                int message_length = 0;
                gl_call(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &message_length));

                std::vector<char> compile_error_message(message_length);
                gl_call(glGetShaderInfoLog(shader_id, message_length, &message_length, &compile_error_message[0]));
                TRIMANA_CORE_ERROR("Failed to compile shader >> {0}", compile_error_message.data());
            }

            gl_call(glAttachShader(shader_program, shader_id));
            shader_ids.push_back(shader_id);
        }

        int result = 0;
        gl_call(glLinkProgram(shader_program));
        gl_call(glGetProgramiv(shader_program, GL_LINK_STATUS, &result));

        if(!result)
        {
            char linker_error_message[1024];
            gl_call(glGetProgramInfoLog(shader_program, sizeof(linker_error_message), nullptr, linker_error_message));
            TRIMANA_CORE_ERROR("Failed to link shader program >> {0}", linker_error_message);
            return;
        }
        
        gl_call(glValidateProgram(shader_program));
        gl_call(glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &result));

        if(!result)
        {
            char validate_error_message[1024];
            gl_call(glGetProgramInfoLog(shader_program, sizeof(validate_error_message), nullptr, validate_error_message));
            TRIMANA_CORE_ERROR("Failed to validate shader program >> {0}", validate_error_message);
            return;
        }

        for(auto& shader_id : shader_ids)
        {
            gl_call(glDetachShader(shader_program, shader_id));
            //gl_call(glDeleteShader(shader_id));
        }

        m_program_id = shader_program;
    }
    
    std::string gl_shader::import_shader(const std::string &file_path)
    {
        std::string result;
        std::ifstream infile(file_path, std::ios::in | std::ios::binary);
        if(infile)
        {
            infile.seekg(0, std::ios::end);
            result.resize(infile.tellg());
            infile.seekg(0, std::ios::beg);
            infile.read(&result[0], result.size());
            infile.close();
            return result;
        }
        else
        {
            TRIMANA_CORE_ERROR("Failed to open file >> {0}", file_path);
            return result = "";
        }
    }

    static GLenum shader_type_from_string(const std::string &type)
    {
        if(type == "vertex")                          return GL_VERTEX_SHADER;
        if(type == "fragment" || type == "pixel")     return GL_FRAGMENT_SHADER;
        if(type == "geometry")                        return GL_GEOMETRY_SHADER;

        TRIMANA_CORE_ERROR("Unknown shader type >> {0}", type);
        return 0;
    }

    std::unordered_map<GLenum,std::string> gl_shader::pre_process(const std::string & source)
    {
        std::unordered_map<GLenum,std::string> shader_sources;

        const char *type_token = "#type";
        size_t type_token_length = strlen(type_token);
        size_t pos = source.find(type_token, 0);

        while(pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            TRIMANA_ASSERT(eol == std::string::npos, "Syntax error, Did you forget to add a new line after #type declaration");

            size_t begin = pos + type_token_length + 1;
            std::string type = source.substr(begin, eol - begin);
            TRIMANA_ASSERT(type != "vertex" && type != "fragment" && type != "pixel" && type != "geometry", "Invalid shader type specified");

            size_t next_line_pos = source.find_first_not_of("\r\n", eol);
            pos = source.find(type_token, next_line_pos);
            shader_sources[shader_type_from_string(type)] = source.substr(next_line_pos, pos - (next_line_pos == std::string::npos ? source.size() - 1 : next_line_pos));
        }

        return shader_sources;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// GL RENDERER /////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    void gl_api_base::set_clear_color(const glm::vec4& color) 
    {
        gl_call(glClearColor(color.r, color.g, color.b, color.a));
    }

    void gl_api_base::clear() 
    {
        gl_call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
    
    void gl_api_base::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void gl_api_base::draw_indexed(const sptr<core::renderer::vertex_array>& vertex_array) 
    {
        auto& index_buffer = vertex_array->get_index_buffer();
        gl_call(glDrawElements(GL_TRIANGLES, index_buffer->get_count(), GL_UNSIGNED_INT, nullptr));
    }


    gl_texture_2d::gl_texture_2d(const std::string & path)
    {
        m_path = path;
        stbi_set_flip_vertically_on_load(1);
        m_local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
        TRIMANA_ASSERT(m_local_buffer == nullptr, "Failed to load image");

        GLenum internal_format = 0, data_format = 0;
        if(m_channels == 4)
        {
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
        }
        else if(m_channels == 3)
        {
            internal_format = GL_RGB8;
            data_format = GL_RGB;
        }

        TRIMANA_ASSERT(internal_format == 0 || data_format == 0, "Format not supported");

        gl_call(glGenTextures(1, &m_renderer_id));
        gl_call(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
        gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        gl_call(glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, data_format, GL_UNSIGNED_BYTE, m_local_buffer));
    }

    gl_texture_2d::~gl_texture_2d()
    {
        stbi_image_free(m_local_buffer);
        gl_call(glDeleteTextures(1, &m_renderer_id));
    }

    void gl_texture_2d::bind(uint32_t slot) const
    {
        gl_call(glActiveTexture(GL_TEXTURE0 + slot));
        gl_call(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
    }

    void gl_texture_2d::unbind() const
    {
        gl_call(glBindTexture(GL_TEXTURE_2D, 0));
    }

}