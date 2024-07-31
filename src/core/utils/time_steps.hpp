#ifndef __time_steps_h__
#define __time_steps_h__

#include "platform_detection.hpp"

namespace core::timers
{
    class TRIMANA_API time_steps
    {
        public:
            time_steps(float delta_time = 0.0f) : m_delta_time(delta_time) {}
            ~time_steps() = default;

            float get_delta_time() const { return m_delta_time; }
            float get_seconds() const { return m_delta_time; }
            float get_milliseconds() const { return m_delta_time * 1000.0f; }
            operator float() const { return m_delta_time; }
            
        private:
            float m_delta_time;
    };
}

#endif // __time_steps_h__