#ifndef __events_h__
#define __events_h__

#include <string>
#include <functional>

#include "log.hpp"
#include "platform_detection.hpp"

/**
 * @def EVENTS_CALLBACK(func)
 * @brief Creates a std::bind object from a member function to be used as a callback for events.
 *
 * This macro takes a member function 'func' as an argument and returns a std::bind object that
 * can be used as a callback for events. The std::bind object is created by binding the member
 * function 'func' to the current object instance (i.e. 'this') and passing the first argument
 * of the member function as a std::placeholder::_1 argument.
 *
 * The resulting std::bind object can be used as a callback for events, and will call the
 * member function 'func' with the first argument passed to the callback as the first argument
 * to the member function.
 *
 * @param[in] func The member function to be bound to the current object as a callback.
 *
 * @return A std::bind object that can be used as a callback for events.
 */
#define EVENTS_CALLBACK(func) std::bind(&func, this, std::placeholders::_1)

namespace core::events
{
    // This enum defines the different categories of events that can occur.
    // The categories are:
    //
    // - `window`: Events related to windows, such as resizing, closing, or changing
    //   the position of a window.
    //
    // - `keyboard`: Events related to keyboard input, such as key presses or releases.
    //
    // - `mouse`: Events related to mouse input, such as button presses or movements.
    //
    // - `unknown`: Events that do not fall into any of the above categories.
    //
    // These categories are used to help filter or handle events in a way that is
    // specific to the application's needs.
    enum class event_category
    {
        window,   // Events related to windows
        keyboard, // Events related to keyboard input
        mouse,    // Events related to mouse input
        unknown   // Events that do not fit into any of the above categories
    };

    // This enum defines the different types of events that can occur. Each event
    // type falls into one of the categories defined by the `event_category`
    // enum. The different types of events are:
    //
    // - `window_resize`: Event indicating that the size of a window has changed.
    //
    // - `window_close`: Event indicating that a window has been closed.
    //
    // - `window_pos_change`: Event indicating that the position of a window has
    //   changed.
    //
    // - `window_maximized`: Event indicating that a window has been maximized.
    //
    // - `window_minimized`: Event indicating that a window has been minimized.
    //
    // - `window_focus_lost`: Event indicating that a window has lost focus.
    //
    // - `window_focus_gain`: Event indicating that a window has gained focus.
    //
    // - `window_frame_resize`: Event indicating that the size of the window frame
    //   has changed.
    //
    // - `keyboard_keypress`: Event indicating that a key has been pressed.
    //
    // - `keyboard_keyrelease`: Event indicating that a key has been released.
    //
    // - `keyboard_keyrepeate`: Event indicating that a key is being repeated.
    //
    // - `keyboard_keychar`: Event indicating that a character has been typed.
    //
    // - `mouse_button_press`: Event indicating that a mouse button has been pressed.
    //
    // - `mouse_button_release`: Event indicating that a mouse button has been
    //   released.
    //
    // - `mouse_wheel_scroll`: Event indicating that the mouse wheel has been scrolled.
    //
    // - `mouse_cursor_pos_change`: Event indicating that the position of the mouse
    //   cursor has changed.
    //
    // - `mouse_cursor_enter`: Event indicating that the mouse cursor has entered
    //   a window.
    //
    // - `mouse_cursor_leave`: Event indicating that the mouse cursor has left a
    //   window.
    //
    enum class event_type
    {
        window_resize,       // Event indicating a window resize
        window_close,        // Event indicating a window close
        window_pos_change,   // Event indicating a window position change
        window_maximized,    // Event indicating a window maximization
        window_minimized,    // Event indicating a window minimization
        window_focus_lost,   // Event indicating a window focus loss
        window_focus_gain,   // Event indicating a window focus gain
        window_frame_resize, // Event indicating a window frame resize

        keyboard_keypress,   // Event indicating a keyboard key press
        keyboard_keyrelease, // Event indicating a keyboard key release
        keyboard_keyrepeate, // Event indicating a keyboard key repetition
        keyboard_keychar,    // Event indicating a keyboard character input

        mouse_button_press,      // Event indicating a mouse button press
        mouse_button_release,    // Event indicating a mouse button release
        mouse_wheel_scroll,      // Event indicating a mouse wheel scroll
        mouse_cursor_pos_change, // Event indicating a mouse cursor position change
        mouse_cursor_enter,      // Event indicating a mouse cursor entry into a window
        mouse_cursor_leave,      // Event indicating a mouse cursor exit from a window
    };

#define EVENT_TYPE_CATEGORY(EVENT_TY, EVENT_CAT)                               \
    static event_type get_static_type() { return EVENT_TY; }                   \
    virtual event_type get_type() const override { return get_static_type(); } \
    virtual event_category get_category() const override { return EVENT_CAT; }

#ifdef _DEBUG
#define EVENTS_ALLOW_TO_SHOW               \
    virtual void show_event_details() = 0; \
    virtual const char *get_event_string() const = 0

#define EVENT_LOG(EVENT, ...)                                                \
    virtual const char *get_event_string() const override { return #EVENT; } \
    virtual void show_event_details() override { TRIMANA_CORE_INFO(__VA_ARGS__); }

#else
#define EVENTS_ALLOW_TO_SHOW
#define EVENT_LOG(EVENT, ...)
#endif

    /**
     * @class event
     * @brief Base class for all event types in Trimana engine.
     *
     * This class is the base class for all event types in the Trimana engine.
     * It provides a common interface for all events and defines the basic
     * operations and attributes that all events should have. It also provides
     * a mechanism to log events in debug mode.
     */
    class TRIMANA_API event
    {
    public:
        /**
         * @brief Default constructor.
         *
         * This constructor is used to create an event object.
         */
        event() = default;

        /**
         * @brief Virtual destructor.
         *
         * This destructor is used to destroy an event object.
         */
        virtual ~event() = default;

        /**
         * @brief Virtual function to get the type of the event.
         *
         * This function is a virtual function that returns the type of the event.
         * It is pure virtual and must be implemented in derived classes.
         *
         * @return The type of the event.
         */
        virtual event_type get_type() const = 0;

        /**
         * @brief Virtual function to get the category of the event.
         *
         * This function is a virtual function that returns the category of the event.
         * It is pure virtual and must be implemented in derived classes.
         *
         * @return The category of the event.
         */
        virtual event_category get_category() const = 0;

        EVENTS_ALLOW_TO_SHOW;

    public:
        /**
         * @brief Flag indicating whether the event is handled or not.
         *
         * This flag is used to indicate whether the event is handled or not.
         * It is used to track whether an event has been processed or not.
         */
        bool handled{false};
    };

    /**
     * @brief The event_handler class handles events.
     */
    class TRIMANA_API event_handler
    {
    public:
        /**
         * @brief Constructor for event_handler class.
         *
         * @param e The event to be handled.
         */
        event_handler(event &e) : m_event(e) {}

        /**
         * @brief Default destructor for event_handler class.
         */
        ~event_handler() = default;

        /**
         * @brief Dispatches the event for handling.
         *
         * This method dispatches the event for handling by a specific function.
         *
         * @tparam Ty The type of event to dispatch.
         * @tparam Func The function to handle the event.
         * @param func The function used to handle the event.
         * @return true if the event is handled successfully, false otherwise.
         */
        template <typename Ty, typename Func>
        bool dispatch(const Func &func)
        {
            if (m_event.get_type() == Ty::get_static_type())
            {
                m_event.handled |= func(static_cast<Ty &>(m_event));
                return true;
            }

            return false;
        }

    private:
        event &m_event; ///< The event being handled by this event_handler.
    };

    using events_callback_func = std::function<void(event &)>;
}

#endif // __events_h__