#ifndef __events_window_h__
#define __events_window_h__

#ifndef __events_h__
#include "events.hpp"
#endif

namespace trimana_core::events
{
    /**
     * @class window_resize_event
     * @brief Event that is triggered when the user resizes a window.
     *
     * This class is an event that is triggered when the user resizes a window. It
     * contains information about the new size of the window, and provides a
     * mechanism for the application to handle this event.
     *
     * The event type of this event is `event_type::window_resize`, and it falls
     * under the category of `event_categoty::window`.
     */
    class TRIMANA_CORE_API window_resize_event : public event
    {
    public:
        /**
         * @brief Constructor.
         *
         * This constructor is used to create an instance of the
         * `window_resize_event` class. It takes two parameters, `width` and
         * `height`, which are the new width and height of the window after the
         * resize, respectively.
         *
         * @param width The new width of the window after the resize.
         * @param height The new height of the window after the resize.
         */
        window_resize_event(int32_t width, int32_t height) : m_width(width), m_height(height) {}

        /**
         * @brief Destructor.
         *
         * This destructor is used to destroy an instance of the
         * `window_resize_event` class.
         */
        virtual ~window_resize_event() = default;

        /**
         * @brief Gets the type of the event.
         *
         * This function returns the type of the event. The type of this event is
         * `event_type::window_resize`.
         *
         * @return The type of the event.
         */
        EVENT_TYPE_CATEGORY(event_type::window_resize, event_category::window);

        /**
         * @brief Logs the event.
         *
         * This function logs the event to the console. It takes a format string
         * and a variable number of arguments, and logs the event using the
         * `trimana_core::log` function.
         *
         * @param fmt The format string to use when logging the event.
         */
        EVENT_LOG(event_type::window_resize, "{0} : ({1}, {2})", get_event_string(), m_width, m_height);

        /**
         * @brief Gets the new width of the window after the resize.
         *
         * This function returns the new width of the window after the resize.
         *
         * @return The new width of the window after the resize.
         */
        int32_t width() const { return m_width; }

        /**
         * @brief Gets the new height of the window after the resize.
         *
         * This function returns the new height of the window after the resize.
         *
         * @return The new height of the window after the resize.
         */
        int32_t height() const { return m_height; }

    private:
        /**
         * @brief The new width of the window after the resize.
         *
         * This field contains the new width of the window after the resize.
         */
        int32_t m_width{NULL};

        /**
         * @brief The new height of the window after the resize.
         *
         * This field contains the new height of the window after the resize.
         */
        int32_t m_height{NULL};
    };

    /**
     * @class window_frame_resize
     * @brief Event triggered when the user resizes the window frame.
     *
     * This class represents an event that is triggered when the user resizes
     * the window frame. It contains information about the new size of the
     * window frame and provides a mechanism for the application to handle this
     * event.
     *
     * The event type of this event is `event_type::window_frame_resize`, and it
     * falls under the category of `event_categoty::window`.
     */
    class TRIMANA_CORE_API window_frame_resize_event : public event
    {
    public:
        /**
         * @brief Constructor.
         *
         * This constructor is used to create an instance of the
         * `window_frame_resize` class. It takes two parameters, `width` and
         * `height`, which are the new width and height of the window frame
         * after the resize, respectively.
         *
         * @param width The new width of the window frame after the resize.
         * @param height The new height of the window frame after the resize.
         */
        window_frame_resize_event(int32_t width, int32_t height) : m_width(width), m_height(height) {}

        /**
         * @brief Destructor.
         *
         * This destructor is the default destructor for the `window_frame_resize`
         * class.
         */
        virtual ~window_frame_resize_event() = default;

        /**
         * @brief Gets the event type category of the event.
         *
         * This function returns the event type category of the event. The event
         * type category of this event is `event_categoty::window`.
         *
         * @return The event type category of the event.
         */
        EVENT_TYPE_CATEGORY(event_type::window_frame_resize, event_category::window);

        /**
         * @brief Logs the event.
         *
         * This function logs the event to the console. It takes a format string
         * and a variable number of arguments, and logs the event using the
         * `trimana_core::log` function.
         *
         * @param fmt The format string to use when logging the event.
         */
        EVENT_LOG(event_type::window_frame_resize, "{0} : ({1}, {2})", get_event_string(), m_width, m_height);

        /**
         * @brief Gets the new width of the window frame after the resize.
         *
         * This function returns the new width of the window frame after the
         * resize.
         *
         * @return The new width of the window frame after the resize.
         */
        int32_t width() const { return m_width; }

        /**
         * @brief Gets the new height of the window frame after the resize.
         *
         * This function returns the new height of the window frame after the
         * resize.
         *
         * @return The new height of the window frame after the resize.
         */
        int32_t height() const { return m_height; }

    private:
        /**
         * @brief The new width of the window frame after the resize.
         *
         * This field contains the new width of the window frame after the resize.
         */
        int32_t m_width{NULL};

        /**
         * @brief The new height of the window frame after the resize.
         *
         * This field contains the new height of the window frame after the resize.
         */
        int32_t m_height{NULL};
    };

    /**
     * @class window_close_event
     * @brief Represents an event that is triggered when a window is closed.
     *
     * This class represents an event that is triggered when a window is closed.
     * It is derived from the base class `event` and provides additional
     * functionality specific to the window close event.
     */
    class TRIMANA_CORE_API window_close_event : public event
    {
    public:
        /**
         * @brief Default constructor.
         *
         * This constructor is used to create an instance of the `window_close_event`
         * class.
         */
        window_close_event() = default;

        /**
         * @brief Destructor.
         *
         * This destructor is called when the `window_close_event` object is destroyed.
         */
        virtual ~window_close_event() = default;

        /**
         * @brief Gets the event type of this event.
         *
         * This function returns the event type of this event. The event type is
         * `event_type::window_close` which indicates that this event represents
         * the closure of a window.
         *
         * @return The event type of this event.
         */
        EVENT_TYPE_CATEGORY(event_type::window_close, event_category::window);

        /**
         * @brief Logs the event string.
         *
         * This function logs the string representation of this event. The event
         * string is automatically generated using the `get_event_string()`
         * function. It is used for debugging purposes.
         */
        EVENT_LOG(event_type::window_close, "{0}", get_event_string());
    };

    /**
     * @brief Represents a window position change event.
     *
     * This class represents a window position change event. It is used to notify
     * other parts of the application about a change in the position of a window.
     */
    class window_pos_change_event : public event
    {
    public:
        /**
         * @brief Constructor.
         *
         * This constructor is used to create an instance of the `window_pos_change_event`
         * class. It takes in the new X and Y coordinates of the window's position.
         *
         * @param pos_x The new X coordinate of the window's position.
         * @param pos_y The new Y coordinate of the window's position.
         */
        window_pos_change_event(int32_t pos_x, int32_t pos_y) : m_posx(pos_x), m_posy(pos_y) {}

        /**
         * @brief Destructor.
         *
         * This destructor is called when the `window_pos_change_event` object is destroyed.
         */
        virtual ~window_pos_change_event() = default;

        /**
         * @brief Gets the event type of this event.
         *
         * This function returns the event type of this event. The event type is
         * `event_type::window_pos_change` which indicates that this event
         * represents a change in the position of a window.
         *
         * @return The event type of this event.
         */
        EVENT_TYPE_CATEGORY(event_type::window_pos_change, event_category::window);

        /**
         * @brief Logs the event string.
         *
         * This function logs the string representation of this event. The event
         * string is automatically generated using the `get_event_string()`
         * function. It is used for debugging purposes.
         */
        EVENT_LOG(event_type::window_pos_change, "{0} : ({1}, {2})", get_event_string(), m_posx, m_posy);

        /**
         * @brief Gets the new X coordinate of the window's position.
         *
         * This function returns the new X coordinate of the window's position.
         *
         * @return The new X coordinate of the window's position.
         */
        int32_t posx() const { return m_posx; }

        /**
         * @brief Gets the new Y coordinate of the window's position.
         *
         * This function returns the new Y coordinate of the window's position.
         *
         * @return The new Y coordinate of the window's position.
         */
        int32_t posy() const { return m_posy; }

    private:
        /**
         * @brief The new X coordinate of the window's position.
         */
        int32_t m_posx{NULL};

        /**
         * @brief The new Y coordinate of the window's position.
         */
        int32_t m_posy{NULL};
    };

    /**
     * @brief Represents an event when the window is minimized.
     *
     * This class defines an event that occurs when the window is minimized.
     */
    class TRIMANA_CORE_API window_minimize_event : public event
    {
    public:
        /**
         * @brief Default constructor for the window_minimize_event class.
         */
        window_minimize_event() = default;

        /**
         * @brief Virtual destructor for the window_minimize_event class.
         */
        virtual ~window_minimize_event() = default;

        /**
         * @brief Defines the category of the event as window_minimized.
         */
        EVENT_TYPE_CATEGORY(event_type::window_minimized, event_category::window);

        /**
         * @brief Logs the event string for the window_minimize_event.
         */
        EVENT_LOG(event_type::window_minimized, "{0}", get_event_string());
    };

    /**
     * @class window_maximize_event
     * @brief Represents an event when the window is maximized.
     *
     * This class defines an event that occurs when the window is maximized.
     * It is a derived class of the base class "event".
     */
    class TRIMANA_CORE_API window_maximize_event : public event
    {
    public:
        /**
         * @brief Default constructor for the window_maximize_event class.
         *
         * This constructor is used to create an instance of the
         * window_maximize_event class.
         */
        window_maximize_event() = default;

        /**
         * @brief Virtual destructor for the window_maximize_event class.
         *
         * This destructor is used to clean up any resources allocated by the
         * window_maximize_event class.
         */
        virtual ~window_maximize_event() = default;

        /**
         * @brief Defines the category of the event as window_maximized.
         *
         * This macro sets the category of the event to "window_maximized".
         * It ensures that the event belongs to the "window" category.
         */
        EVENT_TYPE_CATEGORY(event_type::window_maximized, event_category::window);

        /**
         * @brief Logs the event string for the window_maximize_event.
         *
         * This macro logs the event string for the window_maximize_event.
         * It is used for debugging purposes and ensures that the event
         * string is recorded.
         */
        EVENT_LOG(event_type::window_maximized, "{0}", get_event_string());
    };

    /**
     * @brief Represents an event that occurs when the window loses focus.
     *
     * This class defines an event that occurs when the window loses focus.
     * It is a derived class of the base class "event".
     */
    class TRIMANA_CORE_API window_focus_lost_event : public event
    {
    public:
        /**
         * @brief Default constructor for the window_focus_lost_event class.
         *
         * This constructor is used to create an instance of the
         * window_focus_lost_event class.
         */
        window_focus_lost_event() = default;

        /**
         * @brief Virtual destructor for the window_focus_lost_event class.
         *
         * This destructor is used to clean up any resources allocated by the
         * window_focus_lost_event class.
         */
        virtual ~window_focus_lost_event() = default;

        /**
         * @brief Defines the category of the event as window_focus_lost.
         *
         * This macro sets the category of the event to "window_focus_lost".
         * It ensures that the event belongs to the "window" category.
         */
        EVENT_TYPE_CATEGORY(event_type::window_focus_lost, event_category::window);

        /**
         * @brief Logs the event string for the window_focus_lost_event.
         *
         * This macro logs the event string for the window_focus_lost_event.
         * It is used for debugging purposes and ensures that the event
         * string is recorded.
         */
        EVENT_LOG(event_type::window_focus_lost, "{0}", get_event_string());
    };

    /**
     * @brief Represents a window focus gain event.
     * 
     * This class defines an event that occurs when the window gains focus.
     * It is a derived class of the base class "event".
     */
    class TRIMANA_CORE_API window_focus_gain_event : public event
    {
    public:
        /**
         * @brief Default constructor for the window_focus_gain_event class.
         *
         * This constructor is used to create an instance of the
         * window_focus_gain_event class.
         */
        window_focus_gain_event() = default;

        /**
         * @brief Virtual destructor for the window_focus_gain_event class.
         *
         * This destructor is used to clean up any resources allocated by the
         * window_focus_gain_event class.
         */
        virtual ~window_focus_gain_event() = default;

        /**
         * @brief Defines the category of the event as window_focus_gain.
         *
         * This macro sets the category of the event to "window_focus_gain".
         * It ensures that the event belongs to the "window" category.
         */
        EVENT_TYPE_CATEGORY(event_type::window_focus_gain, event_category::window);

        /**
         * @brief Logs the event string for the window_focus_gain_event.
         *
         * This macro logs the event string for the window_focus_gain_event.
         * It is used for debugging purposes and ensures that the event
         * string is recorded.
         */
        EVENT_LOG(event_type::window_focus_gain, "{0}", get_event_string());
    };
}

#endif //__event_window_h__