#ifndef __events_mouse_h__
#define __events_mouse_h__

#include "events.hpp"

namespace core::events
{
    /**
     * @class mouse_button_press_event
     * @brief Event class representing a mouse button press event.
     * 
     * This class is a subclass of the base Event class and is used to represent
     * mouse button press events. It is used to notify the application about the
     * event of a mouse button being pressed.
     * 
     * The class has a single member variable, m_button, which stores the button
     * that was pressed.
     * 
     * The class also has a constructor that takes an integer parameter, button,
     * which initializes the m_button member variable.
     * 
     * The class has a virtual destructor which ensures proper destruction of
     * the object.
     * 
     * The class defines a macro EVENT_TYPE_CATEGORY which specifies the type of
     * the event and the category of the event.
     * 
     * The class defines a macro EVENT_LOG which logs the event details.
     * 
     * The class has a member function button() which returns the button that was
     * pressed.
     */
    class TRIMANA_API mouse_button_press_event : public event
    {
    public:
        /**
         * @brief Constructor for the mouse_button_press_event class.
         * 
         * @param button The button that was pressed.
         */
        mouse_button_press_event(int32_t button) : m_button(button) {}
        
        /**
         * @brief Destructor for the mouse_button_press_event class.
         */
        virtual ~mouse_button_press_event() = default;

        /**
         * @brief Macro which specifies the type of the event and the category of
         * the event.
         */
        EVENT_TYPE_CATEGORY(event_type::mouse_button_press, event_category::mouse);
        
        /**
         * @brief Macro which logs the event details.
         */
        EVENT_LOG(event_type::mouse_button_press, "{0} : {1}", get_event_string(), m_button);

        /**
         * @brief Returns the button that was pressed.
         * 
         * @return The button that was pressed.
         */
        int32_t button() const { return m_button; }

    private:
        /**
         * @brief The button that was pressed.
         */
        int32_t m_button{NULL};
    };

    /**
     * @class mouse_button_release_event
     * @brief Event class representing a mouse button release event.
     * 
     * This class is a subclass of the base Event class and is used to represent
     * mouse button release events. It is used to notify the application about the
     * event of a mouse button being released.
     * 
     * The class has a single member variable, m_button, which stores the button
     * that was released.
     * 
     * The class also has a constructor that takes an integer parameter, button,
     * which initializes the m_button member variable.
     * 
     * The class has a virtual destructor which ensures proper destruction of
     * the object.
     * 
     * The class defines a macro EVENT_TYPE_CATEGORY which specifies the type of
     * the event and the category of the event.
     * 
     * The class defines a macro EVENT_LOG which logs the event details.
     * 
     * The class has a member function button() which returns the button that was
     * released.
     */
    class TRIMANA_API mouse_button_release_event : public event
    {
    public:
        /**
         * @brief Constructor for the mouse_button_release_event class.
         * 
         * @param button The button that was released.
         */
        mouse_button_release_event(int32_t button) : m_button(button) {}
        
        /**
         * @brief Destructor for the mouse_button_release_event class.
         */
        virtual ~mouse_button_release_event() = default;

        /**
         * @brief Macro which specifies the type of the event and the category of
         * the event.
         */
        EVENT_TYPE_CATEGORY(event_type::mouse_button_release, event_category::mouse);
        
        /**
         * @brief Macro which logs the event details.
         */
        EVENT_LOG(event_type::mouse_button_release, "{0} : {1}", get_event_string(), m_button);

        /**
         * @brief Returns the button that was released.
         * 
         * @return The button that was released.
         */
        int32_t button() const { return m_button; }

    private:
        /**
         * @brief The button that was released.
         */
        int32_t m_button{NULL};
    };

    /**
     * @brief Represents an event that occurs when the mouse wheel is scrolled.
     */
    class TRIMANA_API mouse_wheel_scroll_event : public event
    {
    public:
        /**
         * @brief Constructor for the mouse_wheel_scroll_event class.
         * 
         * @param xoffset The horizontal offset of the scroll.
         * @param yoffset The vertical offset of the scroll.
         */
        mouse_wheel_scroll_event(double xoffset, double yoffset)
            : m_xoffset(xoffset), m_yoffset(yoffset) {}

        /**
         * @brief Destructor for the mouse_wheel_scroll_event class.
         */
        virtual ~mouse_wheel_scroll_event() = default;

        /**
         * @brief Specifies the type of the event and the category of the event.
         */
        EVENT_TYPE_CATEGORY(event_type::mouse_wheel_scroll, event_category::mouse);

        /**
         * @brief Logs the event details.
         */
        EVENT_LOG(event_type::mouse_wheel_scroll, "{0} : {1} , {2}", get_event_string(), m_xoffset, m_yoffset);

        /**
         * @brief Returns the horizontal offset of the scroll.
         * 
         * @return The horizontal offset of the scroll.
         */
        double xoffset() const { return m_xoffset; }

        /**
         * @brief Returns the vertical offset of the scroll.
         * 
         * @return The vertical offset of the scroll.
         */
        double yoffset() const { return m_yoffset; }

    private:
        /**
         * @brief The horizontal offset of the scroll.
         */
        double m_xoffset{0.0};

        /**
         * @brief The vertical offset of the scroll.
         */
        double m_yoffset{0.0};
    };

    // This class represents an event that occurs when the cursor position changes.
    // It derives from the `event` base class.
    class TRIMANA_API mouse_cursorpos_change_event : public event
    {
    public:
        // Constructor for the mouse_cursorpos_change_event class.
        // It takes in the x and y coordinates of the cursor position.
        mouse_cursorpos_change_event(double x, double y) : m_posx(x), m_posy(y) {}

        // Destructor for the mouse_cursorpos_change_event class.
        virtual ~mouse_cursorpos_change_event() = default;

        // Specifies the type of the event and the category of the event.
        // The event type is `event_type::mouse_cursor_pos_change` and the event category is `event_categoty::mouse`.
        EVENT_TYPE_CATEGORY(event_type::mouse_cursor_pos_change, event_category::mouse);

        // Logs the event details.
        // It logs the event type and the x and y coordinates of the cursor position.
        EVENT_LOG(event_type::mouse_cursor_pos_change, "{0} : {1}, {2}", get_event_string(), m_posx, m_posy);

        // Returns the x coordinate of the cursor position.
        double posx() const { return m_posx; }

        // Returns the y coordinate of the cursor position.
        double posy() const { return m_posy; }

    private:
        // The x coordinate of the cursor position.
        double m_posx{0.0};

        // The y coordinate of the cursor position.
        double m_posy{0.0};
    };
    // This class represents an event that occurs when the cursor enters a window.
    // It derives from the `event` base class.
    class TRIMANA_API mouse_cursor_enter_event : public event
    {
    public:
        // Default constructor for the mouse_cursor_enter_event class.
        mouse_cursor_enter_event() = default;

        // Virtual destructor for the mouse_cursor_enter_event class.
        virtual ~mouse_cursor_enter_event() = default;

        // Specifies the type of the event and the category of the event.
        // The event type is `event_type::mouse_cursor_enter` and the event category is `event_categoty::mouse`.
        EVENT_TYPE_CATEGORY(event_type::mouse_cursor_enter, event_category::mouse);

        // Logs the event details.
        // It logs the event type.
        EVENT_LOG(event_type::mouse_cursor_enter, "{0}", get_event_string());
    };

    // This class represents an event that occurs when the cursor leaves a window.
    // It derives from the `event` base class.
    class TRIMANA_API mouse_cursor_leave_event : public event
    {
    public:
        // Default constructor for the mouse_cursor_leave_event class.
        mouse_cursor_leave_event() = default;

        // Virtual destructor for the mouse_cursor_leave_event class.
        virtual ~mouse_cursor_leave_event() = default;

        // Specifies the type of the event and the category of the event.
        // The event type is `event_type::mouse_cursor_leave` and the event category is `event_categoty::mouse`.
        // The `EVENT_TYPE_CATEGORY` macro is a convenience macro that sets the event type and category of the event.
        // It is defined in the `events.hpp` file.
        EVENT_TYPE_CATEGORY(event_type::mouse_cursor_leave, event_category::mouse);

        // Logs the event details.
        // It logs the event type.
        // The `EVENT_LOG` macro is a convenience macro that logs the event details.
        // It is defined in the `events.hpp` file.
        // In this case, it logs the event type using the `get_event_string()` function.
        EVENT_LOG(event_type::mouse_cursor_leave, "{0}", get_event_string());
    };

}

#endif //__events_mouse_h__
