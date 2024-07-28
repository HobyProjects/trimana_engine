#include "application.hpp"

using namespace trimana_core::windows;
using namespace trimana_core::events;
using namespace trimana_core::inputs;
using namespace trimana_core::layers;
using namespace trimana_core::renderer;

// temporary
#include "gl_buffers.hpp"
using namespace trimana_core::renderer::opengl;

namespace trimana_engine::app
{
    application::application()
    {
        m_window = std::make_shared<window>("Trimana Engine");
        events_receiver::set_eventts_callback(m_window, EVENTS_CALLBACK(application::on_events));
        input::target_window(m_window);

        m_layer_stack = std::make_shared<layer_stack>();
        push_layer(std::make_shared<imgui_layer>(m_window));

        // Temporary

        /////////////////////////////////////////////////////////////////////////////

        // Triangle 

        float vertices[] = {
            // Position             // Color
            -0.5f, -0.5f, 0.0f,     0.5f, 1.0f, 0.5f, 1.0f,
             0.5f, -0.5f, 0.0f,     1.0f, 0.5f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f,     0.5f, 1.0f, 0.5f, 1.0f
        };

        m_vertex_array_triangle.reset(create_vertex_array());
        m_vertex_array_triangle->bind();

        std::shared_ptr<vertex_buffers> vertex_buffers_triangle{nullptr};
        vertex_buffers_triangle.reset(create_vertex_buffers(vertices, sizeof(vertices), draw_type::draw_static));

        buffer_layout layout_triangle = {
            {shader_data_type::_3f, "a_position", element_components::xyz},
            {shader_data_type::_4f, "a_color", element_components::rgba}
        };

        vertex_buffers_triangle->set_layout(layout_triangle);
        m_vertex_array_triangle->emplace_vertex_buffer(vertex_buffers_triangle);

        unsigned int indices[3] = {
            0, 1, 2
        };
        
        std::shared_ptr<index_buffers> index_buffer_triangle{nullptr};
        index_buffer_triangle.reset(create_index_buffers(indices, 3, draw_type::draw_static));
        m_vertex_array_triangle->set_index_buffer(index_buffer_triangle);

        m_vertex_array_triangle->unbind();
        m_shader_triangle.reset(create_shader("shaders/main_vertex.glsl", "shaders/main_fragment.glsl"));

        /////////////////////////////////////////////////////////////////////////////

        // Square

        float square_vertices[] = {
            // Position             // Color
            -0.75f, -0.75f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
             0.75f, -0.75f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
             0.75f,  0.75f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
            -0.75f,  0.75f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f
        };

        m_vertex_array_square.reset(create_vertex_array());
        m_vertex_array_square->bind();

        std::shared_ptr<vertex_buffers> vertex_buffers_square{nullptr};
        vertex_buffers_square.reset(create_vertex_buffers(square_vertices, sizeof(square_vertices), draw_type::draw_static));

        buffer_layout layout_square = {
            {shader_data_type::_3f, "a_squre_position", element_components::xyz},
            {shader_data_type::_4f, "a_squre_color", element_components::rgba}
        };

        vertex_buffers_square->set_layout(layout_square);
        m_vertex_array_square->emplace_vertex_buffer(vertex_buffers_square);

        unsigned int square_indices[6] = {
            0, 1, 2, 
            2, 3, 0
        };

        std::shared_ptr<index_buffers> index_buffer_square{nullptr};
        index_buffer_square.reset(create_index_buffers(square_indices, 6, draw_type::draw_static));
        m_vertex_array_square->set_index_buffer(index_buffer_square);

        m_vertex_array_square->unbind();
        m_shader_square.reset(create_shader("shaders/main_vertex_copy.glsl", "shaders/main_fragment_copy.glsl"));

        /////////////////////////////////////////////////////////////////////////////
    }

    void application::run()
    {
        while (m_window->get_attributes().is_active)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Temporary
            m_shader_square->bind();
            m_vertex_array_square->bind();
            glDrawElements(GL_TRIANGLES, m_vertex_array_square->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
            m_vertex_array_square->unbind();
            m_shader_square->unbind();

            m_shader_triangle->bind();
            m_vertex_array_triangle->bind();
            glDrawElements(GL_TRIANGLES, m_vertex_array_triangle->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
            m_vertex_array_triangle->unbind();
            m_shader_triangle->unbind();


            for (std::shared_ptr<layer> layer : *m_layer_stack)
                layer->on_update();

            m_window->swap_buffers();
            events_receiver::poll_events();
        }
    }

    void application::on_events(event &e)
    {
        event_handler handler(e);
        handler.dispatch<window_close_event>(EVENTS_CALLBACK(application::on_window_close));

        for (std::vector<std::shared_ptr<layer>>::reverse_iterator it = m_layer_stack->rbegin(); it != m_layer_stack->rend(); ++it)
        {
            if (e.handled)
                break;
            (*it)->on_event(e);
        }

#ifdef EVENTS_ALLOW_TO_SHOW
        e.show_event_details();
#endif
    }

    void application::push_layer(std::shared_ptr<layer> layer)
    {
        m_layer_stack->push_layer(layer);
        layer->on_attach();
    }

    void application::push_overlay(std::shared_ptr<layer> overlay)
    {
        m_layer_stack->push_overlay(overlay);
        overlay->on_attach();
    }

    bool application::on_window_close(event &e)
    {
        m_window->get_attributes().is_active = false;
        return true;
    }
}