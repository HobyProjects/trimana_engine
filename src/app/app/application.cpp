#include "application.hpp"

using namespace trimana_core::window;
using namespace trimana_core::events;

namespace trimana_engine::app
{
    application::application()
    {
        m_window = std::make_shared<window>("Trimana Engine");
        events_receiver::set_eventts_callback(m_window, EVENTS_CALLBACK(application::on_events));
    }

    void application::run()
    {
        while (m_window->get_attributes().is_active)
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);


            //Do Something

            glfwSwapBuffers(m_window->get_native_window());
            events_receiver::poll_events();
        }
    }

    void application::on_events(trimana_core::events::event &e)
    {
        event_handler handler(e);
        handler.dispatch<window_close_event>(EVENTS_CALLBACK(application::on_window_close));

#ifdef EVENTS_ALLOW_TO_SHOW
        e.show_event_details();
#endif
    }

    bool application::on_window_close(trimana_core::events::event &e)
    {
        m_window->get_attributes().is_active = false;
        return true;
    }
}