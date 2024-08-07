#include "application.hpp"
#include "example_layer.hpp"

using namespace core::windows;
using namespace core::events;
using namespace core::inputs;
using namespace core::layers;
using namespace core::timers;
using namespace gapi::renderer;

namespace engine::app {

  application::application() {
    m_window = std::make_shared<window>("Trimana Engine");
    events_receiver::set_eventts_callback(m_window, EVENTS_CALLBACK(application::on_events));
    input::target_window(m_window);

    m_imgui_layer = std::make_shared<imgui_layer>(m_window);
    push_overlay(m_imgui_layer);
    push_overlay(std::make_shared<example_layer>());
  }

  void application::run() 
  {
    while (m_window->get_attributes().is_active) 
    {
      /////////////////////////////////////////////////////////////////////

      float current_time = static_cast<float>(glfwGetTime());
      time_steps delta_time = current_time - m_last_frame_time;
      m_last_frame_time = current_time;
  
      for (std::shared_ptr<layer> layer : m_layer_stack) 
        layer->on_update(delta_time);

      m_imgui_layer->begin();
      {
        for (std::shared_ptr<layer> layer : m_layer_stack) 
          layer->on_ui_updates();
      } 
      m_imgui_layer->end();

      ///////////////////////////////////////////////////////////////////
        
      m_window->swap_buffers();
      events_receiver::poll_events();
    }
  }

  void application::on_events(event &e) 
  {
    event_handler handler(e);
    handler.dispatch<window_close_event>(EVENTS_CALLBACK(application::on_window_close));

    for (std::vector<core::sptr<layer>>::reverse_iterator it = m_layer_stack.rbegin(); it != m_layer_stack.rend(); ++it) 
    {
      if (e.handled) break;
        (*it)->on_event(e);
    }
  
    #ifdef EVENTS_ALLOW_TO_SHOW
      //e.show_event_details();
    #endif
  }

  void application::push_layer(std::shared_ptr<layer> layer) 
  {
    m_layer_stack.push_layer(layer);
    layer->on_attach();
  }

  void application::push_overlay(std::shared_ptr<layer> overlay) 
  {
    m_layer_stack.push_overlay(overlay);
    overlay->on_attach();
  }

  bool application::on_window_close(event &e) 
  {
    m_window->get_attributes().is_active = false;
    return true;
  }
}  // namespace engine::app