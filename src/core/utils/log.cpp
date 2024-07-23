#include "log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace trimana_core::loggers
{
    /**
     * @brief Shared loggers for core and engine
     */
    std::shared_ptr<spdlog::logger> log::m_core_logger;
    std::shared_ptr<spdlog::logger> log::m_engine_logger;

    /**
     * @brief Initializes the loggers
     *
     * This function initializes the loggers for the core and engine and sets their log levels.
     */
    void log::init_loggers()
    {
        // Create log sinks
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Trimana.log", true));

        // Set log patterns
        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        // Create and set up the core logger
        m_core_logger = std::make_shared<spdlog::logger>("trimana::core", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_core_logger);
        m_core_logger->set_level(spdlog::level::trace);
        m_core_logger->flush_on(spdlog::level::trace);

        // Create and set up the engine logger
        m_engine_logger = std::make_shared<spdlog::logger>("trimana::engine", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_engine_logger);
        m_engine_logger->set_level(spdlog::level::trace);
        m_engine_logger->flush_on(spdlog::level::trace);
    }
}