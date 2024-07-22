#ifndef __events_window_h__
#define __events_window_h__

#ifndef __events_h__
#include "events.hpp"
#endif

namespace trimana_core::events
{
    class TRIMANA_CORE_API window_resize_event : public event
    {
    public:
        window_resize_event(int32_t width, int32_t height) : m_width(width), m_height(height) {}
        virtual ~window_resize_event() = default;

        EVENT_TYPE_CATEGORY(event_type::window_resize, event_categoty::window);
        EVENT_LOG(event_type::window_resize, "{0} : ({1}, {2})", get_event_string(), m_width, m_height);

        int32_t width() const { return m_width; }
        int32_t height() const { return m_height; }

    private:
        int32_t m_width{NULL};
        int32_t m_height{NULL};
    };

    class TRIMANA_CORE_API window_frame_resize : public event
    {
    public:
        window_frame_resize(int32_t width, int32_t height) : m_width(width), m_height(height) {}
        virtual ~window_frame_resize() = default;

        EVENT_TYPE_CATEGORY(event_type::window_frame_resize, event_categoty::window);
        EVENT_LOG(event_type::window_frame_resize, "{0} : ({1}, {2})", get_event_string(), m_width, m_height);

        int32_t width() const { return m_width; }
        int32_t height() const { return m_height; }

    private:
        int32_t m_width{NULL};
        int32_t m_height{NULL};
    };

    class TRIMANA_CORE_API window_close_event : public event
    {
    public:
        window_close_event() = default;
        virtual ~window_close_event() = default;

        EVENT_TYPE_CATEGORY(event_type::window_close, event_categoty::window);
        EVENT_LOG(event_type::window_close, "{0}", get_event_string());
    };

    class window_pos_change : public event
    {
    public:
        window_pos_change(int32_t pos_x, int32_t pos_y) : m_posx(pos_x), m_posy(pos_y) {}
        virtual ~window_pos_change() = default;

        EVENT_TYPE_CATEGORY(event_type::window_pos_change, event_category::window);
        EVENT_LOG(event_type::window_pos_change, "{0} : ({1}, {2})", get_event_string(), m_posx, m_posy);

        int32_t posx() const { return m_posx; }
        int32_t posy() const { return m_posy; }

    private:
        int32_t m_posx{NULL};
        int32_t m_posy{NULL};
    };

    class TRIMANA_CORE_API window_minimize_event : public event
    {
    public:
        window_minimize_event() = default;
        virtual ~window_minimize_event() = default;

        EVENT_TYPE_CATEGORY(event_type::window_minimized, event_category::window);
        EVENT_LOG(event_type::window_minimized, "{0}", get_event_string());
    };

    class TRIMANA_CORE_API window_maximize_event : public event
    {
    public:
        window_maximize_event() = default;
        virtual ~window_maximize_event() = default;

        EVENT_TYPE_CATEGORY(event_type::window_maximized, event_category::window);
        EVENT_LOG(event_type::window_maximized, "{0}", get_event_string());
    }

    class TRIMANA_CORE_API window_focus_lost_event : public event
    {
    public:
        window_focus_lost_event() = default;
        virtual ~window_focus_lost_event() = default;

        EVENT_TYPE_CATEGORY(event_type::window_focus_lost, event_category::window);
        EVENT_LOG(event_type::window_focus_lost, "{0}", get_event_string());
    }

    class TRIMANA_CORE_API window_focus_gain_event : public event
    {
    public:
        window_focus_gain_event() = default;
        virtual ~window_focus_gain_event() = default;

        EVENT_TYPE_CATEGORY(event_type::window_focus_gain, event_category::window);
        EVENT_LOG(event_type::window_focus_gain, "{0}", get_event_string());
    }
}

#endif //__event_window_h__