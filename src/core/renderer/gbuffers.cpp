#include "gbuffers.hpp"

#include "grenderer.hpp"
#include "gl_buffers.hpp"

namespace trimana_core::renderer
{
    vertex_buffers *create_vertex_buffers(float *vertices, size_t size, draw_type type)
    {
        switch (graphic_renderer::get_api())
        {
        case renderer_api::none:
            return nullptr;
        case renderer_api::opengl:
            return new opengl::gl_vertex_buffer(vertices, size, (type == draw_type::draw_dynamic) ? opengl::gl_draw_type::draw_dynamic : opengl::gl_draw_type::draw_static);
        default:
            return nullptr;
        }
    }

    index_buffers *create_index_buffers(unsigned int *indices, size_t count, draw_type type)
    {
        switch (graphic_renderer::get_api())
        {
        case renderer_api::none:
            return nullptr;
        case renderer_api::opengl:
            return new opengl::gl_index_buffer(indices, count, (type == draw_type::draw_dynamic) ? opengl::gl_draw_type::draw_dynamic : opengl::gl_draw_type::draw_static);
        default:
            return nullptr;
        }
    }
}
