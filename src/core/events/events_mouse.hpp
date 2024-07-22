#ifndef __events_mouse_h__
#define __events_mouse_h__

#ifndef __events_h__
#include "events.hpp"
#endif

namespace trimana_core::events
{
    class TRIMANA_CORE_API mouse_button_press_event : public event
    {
    public:
        mouse_button_press_event(int32_t button) : m_button(button) {}
        virtual ~mouse_button_press_event() = default;

        EVENT_TYPE_CATEGORY(event_type::mouse_button_press, event_categoty::mouse);
        EVENT_LOG(event_type::mouse_button_press, "{0} : {1}", get_event_string(), m_button);

        int32_t button() const { return m_button; }

    private:
        int32_t m_button{NULL};
    };

    class TRIMANA_CORE_API mouse_button_release_event : public event
    {
    public:
        mouse_button_release_event(int32_t button) : m_button(button) {}
        virtual ~mouse_button_release_event() = default;

        EVENT_TYPE_CATEGORY(event_type::mouse_button_release, event_categoty::mouse);
        EVENT_LOG(event_type::mouse_button_release, "{0} : {1}", get_event_string(), m_button);

        int32_t button() const { return m_button; }

    private:
        int32_t m_button{NULL};
    };

    class TRIMANA_CORE_API mouse_wheel_scroll_event : public event
    {
    public:
        mouse_wheel_scroll_event(double xoffset, double yoffset) : m_xoffset(xoffset), m_yoffset(yoffset) {}
        virtual ~mouse_wheel_scroll_event() = default;

        EVENT_TYPE_CATEGORY(event_type::mouse_wheel_scroll, event_categoty::mouse);
        EVENT_LOG(event_type::mouse_wheel_scroll, "{0} : {1} , {2}", get_event_string(), m_xoffset, m_yoffset);

        double xoffset() const { return m_xoffset; }
        double yoffset() const { return m_yoffset; }

    private:
        double m_xoffset{0.0}, m_yoffset{0.0};
    };

    class TRIMANA_CORE_API mouse_cursorpos_change_event : public event
    {
    public:
        mouse_cursorpos_change_event(double x, double y) : m_posx(x), m_posy(y) {}
        virtual ~mouse_cursorpos_change_event() = default;

        EVENT_TYPE_CATEGORY(event_type::mouse_cursor_pos_change, event_categoty::mouse);
        EVENT_LOG(event_type::mouse_cursor_pos_change, "{0} : {1}, {2}", get_event_string(), m_posx, m_posy);

        double posx() const { return m_posx; }
        double posy() const { return m_posy; }

    private:
        double m_posx{0.0}, m_posy{0.0};
    };

    class TRIMANA_CORE_API mouse_cursor_enter_event : public event
    {
    public:
        mouse_cursor_enter_event() = default;
        virtual ~mouse_cursor_enter_event() = default;

        EVENT_TYPE_CATEGORY(event_type::mouse_cursor_enter, event_categoty::mouse);
        EVENT_LOG(event_type::mouse_cursor_enter, "{0}", get_event_string());
    };

    class TRIMANA_CORE_API mouse_cursor_leave_event : public event
    {
    public:
        mouse_cursor_leave_event() = default;
        virtual ~mouse_cursor_leave_event() = default;

        EVENT_TYPE_CATEGORY(event_type::mouse_cursor_leave, event_categoty::mouse);
        EVENT_LOG(event_type::mouse_cursor_leave, "{0}", get_event_string());
    };

}

#endif //__events_mouse_h__