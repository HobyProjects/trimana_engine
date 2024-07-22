#ifndef __log_h__
#define __log_h__

// to get smart pointers
#include <memory>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#ifndef __platform_detection_h__
#include "platform_detection.hpp"
#endif

namespace trimana_core::loggers
{
    class TRIMANA_CORE_API log
    {
    public:
        static void init_loggers();
        static std::shared_ptr<spdlog::logger> &get_core_logger() { return m_core_logger; }
        static std::shared_ptr<spdlog::logger> &get_engine_logger() { return m_engine_logger; }

    private:
        static std::shared_ptr<spdlog::logger> m_core_logger;
        static std::shared_ptr<spdlog::logger> m_engine_logger;
    };
}

#define TRIMANA_CORE_TRACE(...) trimana_core::loggers::log::get_core_logger()->trace(__VA_ARGS__)
#define TRIMANA_CORE_INFO(...) trimana_core::loggers::log::get_core_logger()->info(__VA_ARGS__)
#define TRIMANA_CORE_WARN(...) trimana_core::loggers::log::get_core_logger()->warn(__VA_ARGS__)
#define TRIMANA_CORE_ERROR(...) trimana_core::loggers::log::get_core_logger()->error(__VA_ARGS__)
#define TRIMANA_CORE_CRITICAL(...) trimana_core::loggers::log::get_core_logger()->critical(__VA_ARGS__)

#define TRIMANA_TRACE(...) trimana_core::loggers::log::get_engine_logger()->trace(__VA_ARGS__)
#define TRIMANA_INFO(...) trimana_core::loggers::log::get_engine_logger()->info(__VA_ARGS__)
#define TRIMANA_WARN(...) trimana_core::loggers::log::get_engine_logger()->warn(__VA_ARGS__)
#define TRIMANA_ERROR(...) trimana_core::loggers::log::get_engine_logger()->error(__VA_ARGS__)
#define TRIMANA_CRITICAL(...) trimana_core::loggers::log::get_engine_logger()->critical(__VA_ARGS__)

#endif // __log_h__