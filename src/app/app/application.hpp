#ifndef __application_h__
#define __application_h__

#include <events/events_receiver.hpp>
#include <inputs/input.hpp>
#include <layers/imgui_layer.hpp>
#include <layers/layer.hpp>
#include <layers/layer_stack.hpp>
#include <window/window.hpp>

#include <renderer/renderer.hpp>

namespace trimana_engine::app {

  /**
   * @class application
   * @brief Represents the main application class.
   *
   * The application class is responsible for running the application
   * and handling events. It manages the window object and the layer stack.
   */
  class application {
    public:
      /**
       * Default constructor.
       *
       * This constructor is used to create an instance of the
       * application class. It initializes the private member
       * variables and does not take any parameters.
       */
      application();

      /**
       * Destructor.
       *
       * This destructor is used to clean up the resources used
       * by the application. It is called when the application
       * object is destroyed.
       */
      ~application() = default;

      /**
       * Runs the application.
       *
       * This function is responsible for running the application
       * and handling events. It continuously polls for events and
       * processes them. It does not return until the application
       * is closed.
       */
      void main();

      /**
       * Handles events.
       *
       * This function is responsible for handling events. It takes
       * an event object as a parameter and forwards it to the event
       * handler for processing. The event handler decides what to
       * do with the event based on its type.
       *
       * @param e The event object to be handled.
       */
      void on_events(core::events::event& e);

      /**
       * Pushes a layer onto the layer stack.
       *
       * This function is used to push a layer onto the layer stack.
       * The layer will be rendered and updated in the order it was
       * pushed onto the stack.
       *
       * @param layer A shared pointer to the layer to be pushed.
       */
      void push_layer(std::shared_ptr<core::layers::layer> layer);

      /**
       * Pushes an overlay onto the layer stack.
       *
       * This function is used to push an overlay onto the layer stack.
       * The overlay will be rendered and updated on top of the layers
       * in the stack.
       *
       * @param overlay A shared pointer to the overlay to be pushed.
       */
      void push_overlay(std::shared_ptr<core::layers::layer> overlay);

    private:
      /**
       * Handles the window close event.
       *
       * This function is called when the application receives a window close
       * event. It takes a reference to the window close event object as a
       * parameter. The function determines whether the window should be
       * closed based on the event properties. If the window can be closed,
       * it sets the close flag of the window to true, indicating that the
       * window should be closed. The function returns `true` if the window
       * can be closed, and `false` otherwise.
       *
       * @param e The window close event object.
       * @return `true` if the window can be closed, `false` otherwise.
       */
      bool on_window_close(core::events::event& e);

    private:
      /**
       * A shared pointer to the window object.
       *
       * This member variable holds a shared pointer to the window
       * object. It is used to access and control the window
       * functionality.
       */
      std::shared_ptr<core::windows::window> m_window;

      /**
       * A smart pointer that manages the lifetime of an object of type
       * `core::layers::layer_stack`.
       *
       * The `std::shared_ptr` class template is a smart pointer that retains shared
       * ownership of an object through a pointer. Multiple `std::shared_ptr`
       * objects can own the same object. The object is destroyed and its memory
       * deallocated when either of the following happens:
       * - the last remaining `std::shared_ptr` owning the object is destroyed
       * - the last remaining `std::shared_ptr` owning the object is assigned
       * another pointer via the `operator=` or `reset()` member functions
       *
       * In this case, the `std::shared_ptr` is used to manage the lifetime of an
       * object of type `core::layers::layer_stack`.
       */
      std::shared_ptr<core::layers::layer_stack> m_layer_stack;

      std::shared_ptr<core::renderer::shader> m_shader;
      std::shared_ptr<core::renderer::vertex_array> m_vertex_array_triangle;
      std::shared_ptr<core::renderer::vertex_array> m_vertex_array_square;

      core::renderer::orthographic_camera m_camera{-2.0f, 2.0f, -2.0f, 2.0f};
      glm::vec3 m_camera_position{0.0f, 0.0f, 0.0f};
      float m_camera_speed{0.1f};
      float m_camera_rotation{0.0f};
      float m_camera_rotation_speed{0.5f};
};

}  // namespace trimana_engine::app
#endif  // __application_h__