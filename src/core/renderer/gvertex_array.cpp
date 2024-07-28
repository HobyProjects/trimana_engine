#include "gvertex_array.hpp"
#include "grenderer.hpp"

namespace trimana_core::renderer
{
    vertex_array *create_vertex_array()
    {
        switch (graphic_renderer::get_api())
        {
        case renderer_api::none:
            return nullptr;
        case renderer_api::opengl:
            //return new opengl::gl_vertex_buffer(vertices, size, (type == draw_type::draw_dynamic) ? opengl::gl_draw_type::draw_dynamic : opengl::gl_draw_type::draw_static);
        default:
            return nullptr;
        }
    }
}