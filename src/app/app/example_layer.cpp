#include "example_layer.hpp"

using namespace core::inputs;
using namespace core::events;
using namespace core::layers;
using namespace core::timers;

namespace engine::app
{
    void example_layer::on_attach()
    {
        float vertices[] = 
        {
            // Position           // Color
            -0.5f, -0.5f, 0.0f,   0.5f, 1.0f, 0.5f, 1.0f,
             0.5f, -0.5f, 0.0f,   1.0f, 0.5f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f,   0.5f, 1.0f, 0.5f, 1.0f

        };

        unsigned int indices[3] = {0, 1, 2};

        m_vertex_array_triangle = gapi::make_varray<gapi::opengl::gl_vertex_array>();
        m_vertex_array_triangle->bind();

        std::shared_ptr<gapi::vertex_buffer> vertex_buffers_triangle = 
            gapi::make_vertex<gapi::opengl::gl_vertex_buffer>(vertices, sizeof(vertices), gapi::opengl::gl_draw_type::static_daw);

        gapi::buffer_layout layout_triangle = {
            { "a_position", gapi::component::xyz, gapi::data_types::f3 },
            { "a_color", gapi::component::rgba, gapi::data_types::f4  },
        };

        vertex_buffers_triangle->configure_layout(layout_triangle);
        m_vertex_array_triangle->emplace_vbuffer(vertex_buffers_triangle);
        

        std::shared_ptr<gapi::index_buffer> index_buffer_triangle = 
            gapi::make_index<gapi::opengl::gl_index_buffer>(indices, 3, gapi::opengl::gl_draw_type::static_daw);
        m_vertex_array_triangle->emplace_ibuffer(index_buffer_triangle);

        m_shader = gapi::make_shader<gapi::opengl::gl_shader>("main shader", "shaders/main.glsl");
        m_texture_shader = gapi::make_shader<gapi::opengl::gl_shader>("texture shader", "shaders/texture.glsl");

        m_texture = gapi::make_texture<gapi::opengl::gl_texture_2d>("textures/logo-white.png");
        m_texture_new = gapi::make_texture<gapi::opengl::gl_texture_2d>("textures/logo-no-background.png");
        
        m_texture_shader->bind();
        m_texture_shader->uniform("u_texture", (uint32_t)0);

        // ///////////////////////////////////////////////////////////////////////////////

        // Square

        float square_vertices[] = {
            // Position             //Tex coords    // Color
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     0.2f, 0.3f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     0.2f, 0.3f, 0.8f, 1.0f,
             0.5f,  0.5f, 0.0f,     1.0f, 1.0f,     0.2f, 0.3f, 0.8f, 1.0f,
            -0.5f,  0.5f, 0.0f,     0.0f, 1.0f,     0.2f, 0.3f, 0.8f, 1.0f
        };

        // unsigned int square_indices[6] = {0, 1, 2, 2, 3, 0};

        // m_vertex_array_square.reset(create_vertex_array());
        // m_vertex_array_square->bind();
        // {
        // std::shared_ptr<vertex_buffers> vertex_buffers_square{nullptr};
        // vertex_buffers_square.reset(create_vertex_buffers(square_vertices, sizeof(square_vertices), draw_type::draw_static));

        // buffer_layout layout_square = {
        //     {shader_data_type::float_3, "a_position", element_components::xyz},
        //     {shader_data_type::float_2, "a_texcoord", element_components::uv},
        //     {shader_data_type::float_4, "a_color", element_components::rgba}
        // };

        // vertex_buffers_square->set_layout(layout_square);
        // m_vertex_array_square->emplace_vertex_buffer(vertex_buffers_square);

        // std::shared_ptr<index_buffers> index_buffer_square{nullptr};
        // index_buffer_square.reset(create_index_buffers(square_indices, 6, draw_type::draw_static));
        // m_vertex_array_square->set_index_buffer(index_buffer_square);

        // }

        // m_vertex_array_square->unbind();
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