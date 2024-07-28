#include "gl_shader.hpp"
#include "renderer.hpp"

namespace trimana_core::renderer
{
    shader *create_shader(const std::string &vertex_shader, const std::string &fragment_shader)
    {
        switch (graphic_renderer::get_api())
        {
        case renderer_api::none:
            return nullptr;
        case renderer_api::opengl:
            return new opengl::gl_shader(vertex_shader, fragment_shader);
        default:
            TRIMANA_CORE_ERROR("Renderer API is not supported");
            return nullptr;
            break;
        }
    }
}