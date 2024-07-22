#ifndef __events_keyboard_h__
#define __events_keyboard_h__

#ifndef __events_h__
#include "events.hpp"
#endif

namespace trimana_core::events
{
    class TRIMANA_CORE_API keyboard_keypress_event : public event
    {
    public:
        keyboard_keypress_event(int32_t key_code) : m_keycode(key_code) {}
        virtual ~keyboard_keypress_event() = default;

        EVENT_TYPE_CATEGORY(event_type::keyboard_keypress, event_categoty::keyboard);
        EVENT_LOG(event_type::keyboard_keypress, "{0} : {1}", get_event_string(), (int8_t)m_keycode);

        int32_t keycode() const { return m_keycode; }

    private:
        int32_t m_keycode{NULL};
    };

    class TRIMANA_CORE_API keyboard_keyrelease_event : public event
    {
    public:
        keyboard_keyrelease_event(int32_t key_code) : m_keycode(key_code) {}
        virtual ~keyboard_keyrelease_event() = default;

        EVENT_TYPE_CATEGORY(event_type::keyboard_keyrelease, event_categoty::keyboard);
        EVENT_LOG(event_type::keyboard_keyrelease, "{0} : {1}", get_event_string(), (int8_t)m_keycode);

        int32_t keycode() const { return m_keycode; }

    private:
        int32_t m_keycode{NULL};
    };

    class TRIMANA_CORE_API keyboard_keyrepeate_event : public event
    {
    public:
        keyboard_keyrepeate_event(int32_t key_code) : m_keycode(key_code) {}
        virtual ~keyboard_keyrepeate_event() = default;

        EVENT_TYPE_CATEGORY(event_type::keyboard_keyrepeate, event_categoty::keyboard);
        EVENT_LOG(event_type::keyboard_keyrepeate, "{0} : {1}", get_event_string(), (int8_t)m_keycode);

        int32_t keycode() const { return m_keycode; }

    private:
        int32_t m_keycode{NULL};
    };

    class TRIMANA_CORE_API keyboard_keychar_event : public event
    {
    public:
        keyboard_keychar_event(uint32_t code_point) : m_codepoint(code_point) {}
        virtual ~keyboard_keychar_event() = default;

        EVENT_TYPE_CATEGORY(event_type::keyboard_keychar, event_categoty::keyboard);
        EVENT_LOG(event_type::keyboard_keychar, "{0} : {1}", get_event_string(), (uint8_t)m_codepoint);

        uint32_t codepoint() const { return m_codepoint; }

    private:
        uint32_t m_codepoint{NULL};
    };
}

#endif //__events_keyboard_h__