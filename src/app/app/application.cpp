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
    }

    void application::run()
    {
        while (m_window->get_attributes().is_active)
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //Do Something
            for(std::shared_ptr<layer> layer : *m_layer_stack)
                layer->on_update();

            glfwSwapBuffers(m_window->get_native_window());
            events_receiver::poll_events();
        }
    }

    void application::on_events(trimana_core::events::event &e)
    {
        event_handler handler(e);
        handler.dispatch<window_close_event>(EVENTS_CALLBACK(application::on_window_close));

        for(std::vector<std::shared_ptr<layer>>::reverse_iterator it = m_layer_stack->rbegin(); it != m_layer_stack->rend(); ++it)
        {
            if(e.handled)
                break;
            (*it)->on_event(e);
        }

#ifdef EVENTS_ALLOW_TO_SHOW
        e.show_event_details();
#endif
    }

    void application::push_layer(std::shared_ptr<trimana_core::layers::layer> layer)
    {
        m_layer_stack->push_layer(layer);
        layer->on_attach();
    }

    void application::push_overlay(std::shared_ptr<trimana_core::layers::layer> overlay)
    {
        m_layer_stack->push_overlay(overlay);
        overlay->on_attach();
    }

    bool application::on_window_close(trimana_core::events::event &e)
    {
        m_window->get_attributes().is_active = false;
        return true;
    }
}