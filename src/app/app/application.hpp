#ifndef __application_h__
#define __application_h__

#if !defined(__window_h__) && !defined(__events_receiver_h__)
#include <window/window.hpp>
#include <events/events_receiver.hpp>
#endif

namespace trimana_engine::app
{
    /**
     * @class application
     * @brief The main application class.
     *
     * This class represents the main application and is responsible for
     * running the application and handling events. It contains a single
     * instance of a window and forwards events to the event handler for
     * processing.
     */
    class application
    {
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
            void run();

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
            void on_events(trimana_core::events::event& e);

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
            bool on_window_close(trimana_core::events::event& e);

        private:
            /**
             * A shared pointer to the window object.
             *
             * This member variable holds a shared pointer to the window
             * object. It is used to access and control the window
             * functionality.
             */
            std::shared_ptr<trimana_core::window::window> m_window;
    };
}
#endif // __application_h__