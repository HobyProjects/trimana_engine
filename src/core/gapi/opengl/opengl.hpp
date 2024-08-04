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
#include <array>

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
    class TRIMANA_API gl_info
    {
        public:
            gl_info();
            ~gl_info() = default;


            const std::string &gl_version() const { return m_gl_version; }
            const std::string &gl_vendor() const { return m_gl_vendor; }
            const std::string &gl_renderer() const { return m_gl_renderer; }
            const std::string &glsl_version() const { return m_glsl_version; }
            void show() const;

        private:
            std::string m_gl_version;     
            std::string m_gl_vendor;        
            std::string m_gl_renderer;      
            std::string m_glsl_version;     
    };


    class TRIMANA_API gl_context : public renderer::context
    {
    public:
        gl_context(GLFWwindow* window);
        virtual ~gl_context() = default;


        virtual void init() override;
        virtual void swap_buffers() override;
        sptr<gl_info> get_info() const { return m_info; }

    private:
        GLFWwindow* m_window{ nullptr }; 
        sptr<gl_info> m_info{nullptr};
    };


    enum class gl_draw_type
    {
        draw_static   = GL_STATIC_DRAW,
        draw_dynamic  = GL_DYNAMIC_DRAW 
    };


    enum gl_data_type : unsigned int 
    {
        gl_none   = NULL,                
        gl_float  = GL_FLOAT,             
        gl_uint   = GL_UNSIGNED_INT,      
        gl_byte   = GL_BYTE,              
        gl_ubyte  = GL_UNSIGNED_BYTE,     
        gl_int    = GL_INT               
    };


    class TRIMANA_API gl_vertex_buffer : public renderer::vertex_buffers 
    {
        public:
            gl_vertex_buffer(float *vertices, size_t size, gl_draw_type type);
            virtual ~gl_vertex_buffer();


            void bind() const override;
            void unbind() const override;
            virtual const renderer::buffer_layout &get_layout() const override { return m_layout; }
            virtual void set_layout(const renderer::buffer_layout &layout) override { m_layout = layout; }

        private:
            unsigned int m_renderer_id;   
            renderer::buffer_layout m_layout; 
    };

    class TRIMANA_API gl_index_buffer : public renderer::index_buffers 
    {
        public:
            gl_index_buffer(unsigned int *indices, size_t count, gl_draw_type type);
            virtual ~gl_index_buffer();

            void bind() const override;
            void unbind() const override;
            size_t get_count() const override { return m_count; }

        private:
            size_t m_count;          
            unsigned int m_renderer_id; 
    };

    class TRIMANA_API gl_vertex_array : public renderer::vertex_array
    {
        public:
            gl_vertex_array();
            virtual ~gl_vertex_array();

            virtual void bind() const override;
            virtual void unbind() const override;
            virtual void emplace_vertex_buffer(const sptr<renderer::vertex_buffers> &vertex_buffer) override;
            virtual void set_index_buffer(const sptr<renderer::index_buffers> &index_buffer) override;
            const std::vector<sptr<renderer::vertex_buffers>> &get_vertex_buffers() const override { return m_vertex_buffers; }
            const sptr<renderer::index_buffers> &get_index_buffer() const override { return m_index_buffer; }

        private:
            uint32_t m_renderer_id{NULL};    
            std::vector<std::shared_ptr<renderer::vertex_buffers>> m_vertex_buffers; 
            std::shared_ptr<renderer::index_buffers> m_index_buffer; 
    };

    enum class shader_type
    {
        none        = NULL,
        vertex      = GL_VERTEX_SHADER,
        fragment    = GL_FRAGMENT_SHADER  
    };

    class TRIMANA_API gl_shader : public renderer::shader
    {
        public:
            gl_shader(const std::string& path);
            virtual ~gl_shader();

            virtual void bind() const override;
            virtual void unbind() const override;
            virtual bool set_uniform_1i(const std::string &name, int value) override;
            virtual bool set_uniform_1ui(const std::string &name, unsigned int value) override;
            virtual bool set_uniform_1f(const std::string &name, float value) override;
            virtual bool set_uniform_2f(const std::string &name, const glm::vec2 &value) override;
            virtual bool set_uniform_3f(const std::string &name, const glm::vec3 &value) override;
            virtual bool set_uniform_4f(const std::string &name, const glm::vec4 &value) override;
            virtual bool set_uniform_mat4(const std::string &name, const glm::mat4 &value) override;
            virtual bool set_uniform_mat3(const std::string &name, const glm::mat3 &value) override;
            uint32_t get_program_id() const;
            uint32_t get_uniform_location(const std::string &name) const;

        private:
            uint32_t uniform_validator(const std::string &name) const;
            void compile_shader(std::unordered_map<GLenum, std::string> shaders);
            std::string import_shader(const std::string &file_path);
            std::unordered_map<GLenum, std::string> pre_process(const std::string &source);

        private:
            uint32_t m_program_id{NULL};
    };

    class TRIMANA_API gl_api_base : public renderer::renderer_api
    {
    public:
        gl_api_base() = default;
        ~gl_api_base() = default;

        void init() override;
        void draw_indexed(const sptr<renderer::vertex_array>& vertex_array) override;
        void set_clear_color(const glm::vec4& color) override;
        void clear() override;
    };

    class TRIMANA_API gl_texture_2d : public renderer::texture_2d
    {
    public:
        gl_texture_2d(const std::string& path);
        virtual ~gl_texture_2d();

        virtual void bind(uint32_t slot = 0) const override;
        virtual void unbind() const override;
        virtual int32_t width() const override { return m_width; }
        virtual int32_t height() const override { return m_height; }
        virtual uint32_t renderer_id() const override { return m_renderer_id; }
        virtual uint32_t slot() const override { return m_slot; }
        virtual int32_t channels() const override { return m_channels; }
        virtual uint8_t* data() const override { return m_local_buffer; }

    protected:
        uint32_t m_renderer_id{0};
        std::string m_path{};
        int32_t m_slot{0};
        int32_t m_width{0}, m_height{0}, m_channels{0};
        uint8_t* m_local_buffer{nullptr};
    };

} 

#endif // __opengl_h__