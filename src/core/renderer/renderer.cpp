#include "opengl.hpp"

using namespace core::gapi::opengl;

namespace core::renderer
{
    vertex_buffers *create_vertex_buffers(float *vertices, size_t size, draw_type type)
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::none:           return nullptr;
            case renderer_api::api::opengl:         return new gl_vertex_buffer(vertices, size, (type == draw_type::draw_dynamic) ? gl_draw_type::draw_dynamic : gl_draw_type::draw_static);
            default:                                return nullptr;
        }
    }

    index_buffers *create_index_buffers(unsigned int *indices, size_t count, draw_type type)
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::none:       return nullptr;
            case renderer_api::api::opengl:     return new gl_index_buffer(indices, count, (type == draw_type::draw_dynamic) ? gl_draw_type::draw_dynamic : gl_draw_type::draw_static);
            default:                            return nullptr;
        }
    }

    vertex_array *create_vertex_array()
    {
        switch (renderer::get_api())
        {
            case renderer_api::api::none:           return nullptr;
            case renderer_api::api::opengl:         return new gl_vertex_array();
            default:                                return nullptr;
        }
    }

    shader *create_shader(const std::string &vertex_shader, const std::string &fragment_shader)
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::none:       return nullptr;
            case renderer_api::api::opengl:     return new gl_shader(vertex_shader, fragment_shader);
            default:                            return nullptr;
        }
    }

    renderer_api::api renderer_api::s_api = renderer_api::api::opengl;
    std::shared_ptr<renderer_api> render_command::m_renderer_api = std::make_shared<gl_api_base>();

    void renderer::begin_scene()
    {
    }

    void renderer::end_scene()
    {
    }

    void renderer::submit(const std::shared_ptr<vertex_array> &vertex_array)
    {
        vertex_array->bind();
        render_command::api_base_draw_indexed(vertex_array);
    }

}