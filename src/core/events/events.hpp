#ifndef __events_h__
#define __events_h__

#include <string>
#include <functional>

#ifndef __log_h__ && __platform_detection_h__
#include "log.hpp"
#include "platform_detection.hpp"
#endif

namespace trimana_core::events
{
    enum class event_category
    {
        window,
        keyboard,
        mouse,
        unknown
    };

    enum class event_type
    {
        window_resize,
        window_close,
        window_pos_change,
        window_maximized,
        window_minimized,
        window_focus_lost,
        window_focus_gain,
        window_frame_resize,

        keyboard_keypress,
        keyboard_keyrelease,
        keyboard_keyrepeate,
        keyboard_keychar,

        mouse_button_press,
        mouse_button_release,
        mouse_wheel_scroll,
        mouse_cursor_pos_change,
        mouse_cursor_enter,
        mouse_cursor_leave
    };

#define EVENT_TYPE_CATEGORY(EVENT_TY, EVENT_CAT)                             \
    static event_type get_static_type() { return EVENT_TY; }                   \
    virtual event_type get_type() const override { return get_static_type(); } \
    virtual event_category get_category() const override { return EVENT_CAT; }

#ifdef _DEBUG
#define EVENTS_ALLOW_TO_SHOW               \
    virtual void show_event_datails() = 0; \
    virtual const char *get_event_string() const = 0

#define EVENT_LOG(EVENT, ...)                                                \
    virtual const char *get_event_string() const override { return #EVENT; } \
    virtual void show_event_details() override { TRIMANA_CORE_INFO(__VA_ARGS__); }

#else
#define EVENTS_ALLOW_TO_SHOW
#define EVENT_LOG(EVENT, ...)
#endif

    class TRIMANA_CORE_API event
    {
    public:
        event() = default;
        virtual ~event() = default;
        virtual event_type get_type() const = 0;
        virtual event_category get_category() const = 0;
        EVENTS_ALLOW_TO_SHOW;

    public:
        bool handled{false};
    };

    class TRIMANA_CORE_API event_handler
    {
    public:
        event_handler(event &e) : m_event(e) {}
        ~event_handler() = default;

        template <typename Ty, typename Func>
        bool disspatch(const Func &func)
        {
            if (m_event.get_type() == Ty::get_static_type)
            {
                m_event.handled |= func(static_cast<Ty &>(m_event));
                return true;
            }

            return false;
        }

    private:
        event &m_event;
    };

}

#endif // __events_h__