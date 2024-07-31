#include "opengl.hpp"
#include "renderer.hpp"

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
    glm::mat4 renderer::m_view_projection_matrix = glm::mat4(1.0f);

    void renderer::begin_scene( const glm::mat4& camera_projection)
    {
        m_view_projection_matrix = camera_projection;
    }

    void renderer::end_scene()
    {
    }

    void renderer::submit(const std::shared_ptr<shader>& shader_ptr, const std::shared_ptr<vertex_array> &vertex_array, const glm::mat4& model_matrix)
    {
        shader_ptr->bind();
        shader_ptr->set_uniform_mat4f("u_projection_view", m_view_projection_matrix);
        shader_ptr->set_uniform_mat4f("u_model", model_matrix);

        vertex_array->bind();
        render_command::api_base_draw_indexed(vertex_array);
    }

    orthographic_camera::orthographic_camera(float left, float right, float bottom, float top)
    {
        m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_view_projection = m_projection * m_view;
    }

    void orthographic_camera::recalculate_view_matrix()
    {
        glm::mat4 transform = glm::translate(
            glm::mat4(1.0f), m_position) * 
            glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0, 0, 1)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0, 1, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1, 0, 0));

        m_view = glm::inverse(transform);
        m_view_projection = m_projection * m_view;
    }

}
