#include "example_layer.hpp"
#include <gapi/gapi_renderer.hpp>

using namespace core::inputs;
using namespace core::events;
using namespace core::layers;
using namespace core::timers;
using namespace gapi;

namespace engine::app
{

    void example_layer::on_attach()
    {
        m_renderer = std::make_shared<gapir::gl_renderer>();

        float vertices[] = 
        {
            // Position           // Color
            -0.5f, -0.5f, 0.0f,   0.5f, 1.0f, 0.5f, 1.0f,
             0.5f, -0.5f, 0.0f,   1.0f, 0.5f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f,   0.5f, 1.0f, 0.5f, 1.0f

        };

        unsigned int indices[3] = {0, 1, 2};

        m_vertex_array_triangle = ggl::make_array();
        m_vertex_array_triangle->bind();
        std::shared_ptr<gapi::vertex_buffer> vertex_buffers_triangle = ggl::make_vertex(vertices, sizeof(vertices), ggl::DRAW_STATIC);

        gapi::buffer_layout layout_triangle = {
            { "a_position",  XYZ, F3  },
            { "a_color",    RGBA, F4  },
        };

        vertex_buffers_triangle->configure_layout(layout_triangle);
        m_vertex_array_triangle->emplace_vertex(vertex_buffers_triangle);
        std::shared_ptr<index_buffer> index_buffer_triangle = ggl::make_index(indices, 3, ggl::DRAW_STATIC);
        m_vertex_array_triangle->emplace_index(index_buffer_triangle);

        // ///////////////////////////////////////////////////////////////////////////////

        // Square

        float square_vertices[] = {
            // Position             //Tex coords    // Color
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     0.2f, 0.3f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     0.2f, 0.3f, 0.8f, 1.0f,
             0.5f,  0.5f, 0.0f,     1.0f, 1.0f,     0.2f, 0.3f, 0.8f, 1.0f,
            -0.5f,  0.5f, 0.0f,     0.0f, 1.0f,     0.2f, 0.3f, 0.8f, 1.0f
        };

        unsigned int square_indices[6] = {0, 1, 2, 2, 3, 0};

        m_vertex_array_square = ggl::make_array();
        m_vertex_array_square->bind();
        {
            std::shared_ptr<vertex_buffer> vertex_buffers_square = ggl::make_vertex(square_vertices, sizeof(square_vertices), ggl::DRAW_STATIC);

            buffer_layout layout_square = {
                { "a_position", XYZ,  F3 },
                { "a_texcoord",  UV,  F2 },
                { "a_color",    RGBA, F4 }
            };

            vertex_buffers_square->configure_layout(layout_square);
            m_vertex_array_square->emplace_vertex(vertex_buffers_square);
            std::shared_ptr<index_buffer> index_buffer_square = ggl::make_index(square_indices, 6,  ggl::DRAW_STATIC);
            m_vertex_array_square->emplace_index(index_buffer_square);

        }
        m_vertex_array_square->unbind();

        m_shader = ggl::make_shader("main shader", "shaders/main.glsl");
        m_texture_shader = ggl::make_shader("texture shader", "shaders/texture.glsl");

        m_texture = ggl::make_texture2d("textures/logo-white.png", ggl::TEX_FILTER_LINEAR, ggl::TEX_WRAP_CLAMP);
        m_texture_new = make_texture2d("textures/logo-no-background.png", ggl::TEX_FILTER_LINEAR, ggl::TEX_WRAP_CLAMP);
        
        m_texture_shader->bind();
        m_texture_shader->uniform("u_texture", (uint32_t)0);

    }

    void example_layer::on_detach()
    {

    }

    void example_layer::on_update(core::timers::time_steps ts)
    {
        ////////////////////////////////////////////////////////////////////
      
        // if(input::is_key_pressed(GLFW_KEY_W))
        //     m_camera_position.y += m_camera_speed * ts;
        // if(input::is_key_pressed(GLFW_KEY_S))
        //     m_camera_position.y -= m_camera_speed * ts;
        // if(input::is_key_pressed(GLFW_KEY_A))
        //     m_camera_position.x -= m_camera_speed * ts;
        // if(input::is_key_pressed(GLFW_KEY_D))
        //     m_camera_position.x += m_camera_speed * ts;

        // if(input::is_key_pressed(GLFW_KEY_Q))
        //     m_camera_rotation += m_camera_rotation_speed * ts;
        // if(input::is_key_pressed(GLFW_KEY_E))
        //     m_camera_rotation -= m_camera_rotation_speed * ts;

        ////////////////////////////////////////////////////////////////////

        // render_command::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
        // render_command::clear();

        // m_camera.set_position(m_camera_position);
        // m_camera.set_rotation(glm::vec3(0.0f, 0.0f, m_camera_rotation));

        // renderer::begin_scene(m_camera.get_view_projection());
        // glm::mat4 scaler = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

        // m_shader->bind();
        // m_shader->set_uniform_4f("u_color", m_color);

        // for(int x = 0; x < 20; x++)
        // {
        //     for(int y = 0; y < 20; y++)
        //     {
        //         glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
        //         glm::mat4 treansform = glm::translate(glm::mat4(1.0f), pos) * scaler;
        //         renderer::submit(m_shader, m_vertex_array_square, treansform);
        //     }
        // }

        // m_texture->bind();
        // renderer::submit(m_texture_shader, m_vertex_array_square, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // m_texture_new->bind();
        // renderer::submit(m_texture_shader, m_vertex_array_square, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


        // // renderer::submit(m_shader, m_vertex_array_triangle);
        // renderer::end_scene();


        ////////////////////////////////////////////////////////////////////

        m_renderer->clear_color(0.1f, 0.1f, 0.1f, 1.0f);
        m_renderer->clear();

        m_shader->bind();
        m_renderer->submit(m_vertex_array_triangle);
    }

    void example_layer::on_ui_updates()
    {
        ImGui::Begin("Settings");
        // ImGui::ColorEdit4("Square Color", glm::value_ptr(m_color));
        ImGui::End();
    }

    void example_layer::on_event(core::events::event & e)
    {

    }
}