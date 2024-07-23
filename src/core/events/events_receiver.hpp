#ifndef __events_receiver_h__
#define __events_receiver_h__

#ifndef __events_h__
#include "events.hpp"
#endif

#if !defined(__events_keyboard_h__) && !defined(__events_mouse_h__) && !defined(__events_window_h__)
#include "events_window.hpp"
#include "events_keyboard.hpp"
#include "events_mouse.hpp"
#endif

#ifndef __window_h__
#include "window.hpp"
#endif

namespace trimana_core::events
{
    /**
     * @class events_receiver
     * @brief This class is responsible for receiving and processing events.
     *
     * This class is a singleton that is used to receive and process events in the
     * Trimana engine. It provides a mechanism to poll events and  set  callback
     * functions  to  handle  events.  The  events   are   received   from   the
     * platform-specific event system and are processed by the event handler.
     */
    class TRIMANA_CORE_API events_receiver
    {
    private:
        // Private constructor to prevent instantiation of this class.
        events_receiver() = default;

        // Copy constructor and copy assignment operator are deleted to prevent
        // accidental object copying.
        events_receiver(const events_receiver &) = delete;
        events_receiver &operator=(const events_receiver &) = delete;

        // Move constructor is defaulted to allow for move semantics.
        events_receiver(events_receiver &&) = default;

    public:
        /**
         * @brief Polls for events and processes them.
         *
         * This function is responsible for polling for events and processing
         * them. It retrieves the events from the platform-specific event system
         * and forwards them to the event handler for processing.
         */
        static void poll_events();

        /**
         * @brief Sets the callback function for handling events.
         *
         * This function sets the callback function that will be called when
         * events  are  received.  The  callback  function  is  responsible  for
         * handling the events and performing any necessary actions based on the
         * event type.
         *
         * @param window The window object for which the events are being handled.
         * @param callback The callback function to be called when events occur.
         */
        static void set_eventts_callback(std::shared_ptr<trimana_core::window::window> window, const events_callback_func &callback);

    private:
        // The callback function that will be called when events occur.
        static events_callback_func m_events_callback;

        // The weak pointer to the window object for which the events are being
        // handled. This is used to prevent circular references and to allow the
        // window object to be destroyed if it is no longer needed.
        static std::weak_ptr<trimana_core::window::window> m_window;
    };
}

#endif // __events_receiver_h__