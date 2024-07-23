#ifndef __events_keyboard_h__
#define __events_keyboard_h__

#ifndef __events_h__
#include "events.hpp"
#endif

namespace trimana_core::events
{
    /**
     * @class keyboard_keypress_event
     * @brief Event representing a keyboard key press event.
     * 
     * This class represents a keyboard key press event. It inherits from the
     * event base class and provides additional functionality for handling
     * keyboard key press events.
     */
    class TRIMANA_CORE_API keyboard_keypress_event : public event
    {
    public:
        /**
         * @brief Constructs a keyboard_keypress_event object.
         * 
         * @param key_code The key code of the pressed key.
         */
        keyboard_keypress_event(int32_t key_code) : m_keycode(key_code) {}

        /**
         * @brief Destructor for the keyboard_keypress_event class.
         * 
         */
        virtual ~keyboard_keypress_event() = default;

        /**
         * @brief Get the event type category.
         * 
         * @return The event type category.
         */
        EVENT_TYPE_CATEGORY(event_type::keyboard_keypress, event_category::keyboard);

        /**
         * @brief Get the event log.
         * 
         * @return The event log.
         */
        EVENT_LOG(event_type::keyboard_keypress, "{0} : {1}", get_event_string(), (int8_t)m_keycode);

        /**
         * @brief Get the key code of the pressed key.
         * 
         * @return The key code.
         */
        int32_t keycode() const { return m_keycode; }

    private:
        /**
         * @brief The key code of the pressed key.
         */
        int32_t m_keycode{NULL};
    };

    /**
     * @class keyboard_keyrelease_event
     * @brief Event representing a keyboard key release event.
     * 
     * This class represents a keyboard key release event. It inherits from the
     * event base class and provides additional functionality for handling
     * keyboard key release events.
     */
    class TRIMANA_CORE_API keyboard_keyrelease_event : public event
    {
    public:
        /**
         * @brief Constructs a keyboard_keyrelease_event object.
         * 
         * @param key_code The key code of the released key.
         */
        keyboard_keyrelease_event(int32_t key_code) : m_keycode(key_code) {}

        /**
         * @brief Destructor for the keyboard_keyrelease_event class.
         * 
         */
        virtual ~keyboard_keyrelease_event() = default;

        /**
         * @brief Get the event type category.
         * 
         * @return The event type category.
         */
        EVENT_TYPE_CATEGORY(event_type::keyboard_keyrelease, event_category::keyboard);

        /**
         * @brief Get the event log.
         * 
         * @return The event log.
         */
        EVENT_LOG(event_type::keyboard_keyrelease, "{0} : {1}", get_event_string(), (int8_t)m_keycode);

        /**
         * @brief Get the key code of the released key.
         * 
         * @return The key code.
         */
        int32_t keycode() const { return m_keycode; }

    private:
        /**
         * @brief The key code of the released key.
         */
        int32_t m_keycode{NULL};
    };

    /**
     * @class keyboard_keyrepeate_event
     * @brief Event representing a keyboard key repetition event.
     * 
     * This class represents a keyboard key repetition event. It inherits from the
     * event base class and provides additional functionality for handling
     * keyboard key repetition events.
     */
    class TRIMANA_CORE_API keyboard_keyrepeate_event : public event
    {
    public:
        /**
         * @brief Constructs a keyboard_keyrepeate_event object.
         * 
         * @param key_code The key code of the repeated key.
         */
        keyboard_keyrepeate_event(int32_t key_code) : m_keycode(key_code) {}

        /**
         * @brief Destructor for the keyboard_keyrepeate_event class.
         * 
         */
        virtual ~keyboard_keyrepeate_event() = default;

        /**
         * @brief Get the event type category.
         * 
         * @return The event type category.
         */
        EVENT_TYPE_CATEGORY(event_type::keyboard_keyrepeate, event_category::keyboard);

        /**
         * @brief Get the event log.
         * 
         * @return The event log.
         */
        EVENT_LOG(event_type::keyboard_keyrepeate, "{0} : {1}", get_event_string(), (int8_t)m_keycode);

        /**
         * @brief Get the key code of the repeated key.
         * 
         * @return The key code.
         */
        int32_t keycode() const { return m_keycode; }

    private:
        /**
         * @brief The key code of the repeated key.
         */
        int32_t m_keycode{NULL};
    };

    /**
     * @class keyboard_keychar_event
     * @brief Event representing a keyboard character input event.
     * 
     * This class represents a keyboard character input event. It inherits from the
     * event base class and provides additional functionality for handling
     * keyboard character input events.
     */
    class TRIMANA_CORE_API keyboard_keychar_event : public event
    {
    public:
        /**
         * @brief Constructs a keyboard_keychar_event object.
         * 
         * @param code_point The code point of the input character.
         */
        keyboard_keychar_event(uint32_t code_point) : m_codepoint(code_point) {}

        /**
         * @brief Destructor for the keyboard_keychar_event class.
         * 
         */
        virtual ~keyboard_keychar_event() = default;

        /**
         * @brief Get the event type category.
         * 
         * @return The event type category.
         */
        EVENT_TYPE_CATEGORY(event_type::keyboard_keychar, event_category::keyboard);

        /**
         * @brief Get the event log.
         * 
         * @return The event log.
         */
        EVENT_LOG(event_type::keyboard_keychar, "{0} : {1}", get_event_string(), (uint8_t)m_codepoint);

        /**
         * @brief Get the code point of the input character.
         * 
         * @return The code point.
         */
        uint32_t codepoint() const { return m_codepoint; }

    private:
        /**
         * @brief The code point of the input character.
         */
        uint32_t m_codepoint{NULL};
    };
}

#endif //__events_keyboard_h__