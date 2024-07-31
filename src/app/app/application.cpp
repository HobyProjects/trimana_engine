#include "application.hpp"

using namespace core::windows;
using namespace core::events;
using namespace core::inputs;
using namespace core::layers;
using namespace core::renderer;
using namespace core::gapi::opengl;
using namespace core::timers;

namespace trimana_engine::app {

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

    float vertices[] = 
    {
      // Position           // Color
      -0.5f, -0.5f, 0.0f,   0.5f, 1.0f, 0.5f, 1.0f,
        0.5f, -0.5f, 0.0f,   1.0f, 0.5f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f,   0.5f, 1.0f, 0.5f, 1.0f

    };

    m_vertex_array_triangle.reset(create_vertex_array());
    m_vertex_array_triangle->bind();

    std::shared_ptr<vertex_buffers> vertex_buffers_triangle{nullptr};
    vertex_buffers_triangle.reset(create_vertex_buffers(vertices, sizeof(vertices), draw_type::draw_static));

    buffer_layout layout_triangle = 
    {
      {shader_data_type::float_3, "a_position", element_components::xyz},
      {shader_data_type::float_4, "a_color", element_components::rgba},
    };

    vertex_buffers_triangle->set_layout(layout_triangle);

    m_vertex_array_triangle->emplace_vertex_buffer(vertex_buffers_triangle);
    
    unsigned int indices[3] = {0, 1, 2};

    std::shared_ptr<index_buffers> index_buffer_triangle{nullptr};
    index_buffer_triangle.reset(create_index_buffers(indices, 3, draw_type::draw_static));
    m_vertex_array_triangle->set_index_buffer(index_buffer_triangle);

    m_shader.reset(create_shader("shaders/main_vertex.glsl", "shaders/main_fragment.glsl"));

    ///////////////////////////////////////////////////////////////////////////////

    // Square

    float square_vertices[] = 
    {
      // Position             // Color
      -0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
        0.5f,  0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
      -0.5f,  0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f
    };

    unsigned int square_indices[6] = {0, 1, 2, 2, 3, 0};

    m_vertex_array_square.reset(create_vertex_array());
    m_vertex_array_square->bind();
    {
      std::shared_ptr<vertex_buffers> vertex_buffers_square{nullptr};
      vertex_buffers_square.reset(create_vertex_buffers(square_vertices, sizeof(square_vertices), draw_type::draw_static));

      buffer_layout layout_square = 
      {
        {shader_data_type::float_3, "a_position", element_components::xyz},
        {shader_data_type::float_4, "a_color", element_components::rgba}
      };

      vertex_buffers_square->set_layout(layout_square);
      m_vertex_array_square->emplace_vertex_buffer(vertex_buffers_square);

      std::shared_ptr<index_buffers> index_buffer_square{nullptr};
      index_buffer_square.reset(create_index_buffers(square_indices, 6, draw_type::draw_static));
      m_vertex_array_square->set_index_buffer(index_buffer_square);

    }
    m_vertex_array_square->unbind();

    /////////////////////////////////////////////////////////////////////////////

  }

  void application::main() 
  {
    while (m_window->get_attributes().is_active) 
    {
      float current_time = static_cast<float>(glfwGetTime());
      time_steps delta_time = current_time - m_last_frame_time;
      m_last_frame_time = current_time;
      TRIMANA_INFO("Delta time: {0}s ({1}ms)", delta_time.get_seconds(), delta_time.get_milliseconds());
      
      ////////////////////////////////////////////////////////////////////
      
      if(input::is_key_pressed(GLFW_KEY_W))
        m_camera_position.y += m_camera_speed * delta_time;
      if(input::is_key_pressed(GLFW_KEY_S))
        m_camera_position.y -= m_camera_speed * delta_time;
      if(input::is_key_pressed(GLFW_KEY_A))
        m_camera_position.x -= m_camera_speed * delta_time;
      if(input::is_key_pressed(GLFW_KEY_D))
        m_camera_position.x += m_camera_speed * delta_time;

      if(input::is_key_pressed(GLFW_KEY_Q))
        m_camera_rotation += m_camera_rotation_speed * delta_time;
      if(input::is_key_pressed(GLFW_KEY_E))
        m_camera_rotation -= m_camera_rotation_speed * delta_time;

      ////////////////////////////////////////////////////////////////////

      if(input::is_key_pressed(GLFW_KEY_UP))
        m_model_position.y += m_model_speed * delta_time;
      if(input::is_key_pressed(GLFW_KEY_DOWN))
        m_model_position.y -= m_model_speed * delta_time;
      if(input::is_key_pressed(GLFW_KEY_LEFT))
        m_model_position.x -= m_model_speed * delta_time;
      if(input::is_key_pressed(GLFW_KEY_RIGHT))
        m_model_position.x += m_model_speed * delta_time;

      ///////////////////////////////////////////////////////////////////

      render_command::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
      render_command::clear();

      m_camera.set_position(m_camera_position);
      m_camera.set_rotation(glm::vec3(0.0f, 0.0f, m_camera_rotation));

      renderer::begin_scene(m_camera.get_view_projection());
      glm::mat4 scaler = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

      for(int x = 0; x < 20; x++)
      {
        for(int y = 0; y < 20; y++)
        {
          glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
          glm::mat4 treansform = glm::translate(glm::mat4(1.0f), pos) * scaler;
          renderer::submit(m_shader, m_vertex_array_square, treansform);
        }
      }

      renderer::submit(m_shader, m_vertex_array_triangle);
      renderer::end_scene();

      for (std::shared_ptr<layer> layer : *m_layer_stack) 
        layer->on_update(delta_time);

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
      if (e.handled) break;
        (*it)->on_event(e);
    }
  
    #ifdef EVENTS_ALLOW_TO_SHOW
      //e.show_event_details();
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
}  // namespace trimana_engine::app