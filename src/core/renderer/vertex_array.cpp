#include "vertex_array.hpp"
#include "renderer.hpp"

#include "gl_vertex_array.hpp"

namespace trimana_core::renderer
{
    vertex_array *create_vertex_array()
    {
        switch (graphic_renderer::get_api())
        {
        case renderer_api::none:
            return nullptr;

        case renderer_api::opengl:
            return new opengl::gl_vertex_array();
            
        default:
            return nullptr;
        }
    }
}