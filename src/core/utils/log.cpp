#include "log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace trimana_core::loggers
{
    std::shared_ptr<spdlog::logger> log::m_core_logger;
    std::shared_ptr<spdlog::logger> log::m_engine_logger;

    void log::init_loggers()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Trimana.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        m_core_logger = std::make_shared<spdlog::logger>("trimana::core", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_core_logger);
        m_core_logger->set_level(spdlog::level::trace);
        m_core_logger->flush_on(spdlog::level::trace);

        m_engine_logger = std::make_shared<spdlog::logger>("trimana::engine", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_engine_logger);
        m_engine_logger->set_level(spdlog::level::trace);
        m_engine_logger->flush_on(spdlog::level::trace);
    }
}