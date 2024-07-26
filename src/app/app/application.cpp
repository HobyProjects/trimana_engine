#include "application.hpp"

using namespace trimana_core::windows;
using namespace trimana_core::events;
using namespace trimana_core::inputs;
using namespace trimana_core::layers;

namespace trimana_engine::app
{
    application::application()
    {
        m_window = std::make_shared<window>("Trimana Engine");
        events_receiver::set_eventts_callback(m_window, EVENTS_CALLBACK(application::on_events));
        input::target_window(m_window);

        m_layer_stack = std::make_shared<layer_stack>();
        push_layer(std::make_shared<imgui_layer>(m_window));

        glGenVertexArrays(1, &m_vertex_array);
        glBindVertexArray(m_vertex_array);

        glGenBuffers(1, &m_vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);

        unsigned int indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    void application::run()
    {
        while (m_window->get_attributes().is_active)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(m_vertex_array);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);

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
        glDeleteVertexArrays(1, &m_vertex_array);
        glDeleteBuffers(1, &m_vertex_buffer);
        glDeleteBuffers(1, &m_index_buffer);
        
        m_window->get_attributes().is_active = false;
        return true;
    }
}