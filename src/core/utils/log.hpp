#ifndef __log_h__
#define __log_h__

// to get smart pointers
#include <memory>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include "platform_detection.hpp"

namespace core::loggers
{
    /**
     * @brief A class managing the instantiation and retrieval of loggers for the
     *        Trimana library.
     * 
     * This class is a singleton, meaning that only one instance of it can exist
     * in the entire program. We use this singleton to manage the instantiation
     * of the loggers, so that we can have a single point of access to the loggers
     * from all over the program.
     * 
     * The loggers are stored as static member variables of the class, which
     * means that they are only created once, when the class is first accessed.
     * The loggers are created in the `init_loggers` method, which is called
     * implicitly when the class is first accessed.
     * 
     * The loggers are then retrieved using the `get_core_logger` and
     * `get_engine_logger` methods, which return a reference to the logger.
     * This allows the loggers to be used from any part of the program, without
     * having to worry about the lifetime of the logger.
     */
    class TRIMANA_API log
    {
    public:
        /**
         * @brief Initializes the loggers.
         * 
         * This method is called implicitly when the class is first accessed.
         */
        static bool init_loggers();

        /**
         * @brief Returns a reference to the core logger.
         * 
         * The core logger is the logger that is used for logging messages that
         * are related to the Trimana library itself.
         * 
         * @return A reference to the core logger.
         */
        static std::shared_ptr<spdlog::logger> &get_core_logger() { return m_core_logger; }

        /**
         * @brief Returns a reference to the engine logger.
         * 
         * The engine logger is the logger that is used for logging messages that
         * are related to the engine.
         * 
         * @return A reference to the engine logger.
         */
        static std::shared_ptr<spdlog::logger> &get_engine_logger() { return m_engine_logger; }

    private:
        /**
         * @brief The core logger.
         * 
         * The core logger is the logger that is used for logging messages that
         * are related to the Trimana library itself.
         */
        static std::shared_ptr<spdlog::logger> m_core_logger;

        /**
         * @brief The engine logger.
         * 
         * The engine logger is the logger that is used for logging messages that
         * are related to the engine.
         */
        static std::shared_ptr<spdlog::logger> m_engine_logger;
    };
}


// Define macros for logging with the core logger.
#define TRIMANA_CORE_TRACE(...) core::loggers::log::get_core_logger()->trace(__VA_ARGS__)
#define TRIMANA_CORE_INFO(...) core::loggers::log::get_core_logger()->info(__VA_ARGS__)
#define TRIMANA_CORE_WARN(...) core::loggers::log::get_core_logger()->warn(__VA_ARGS__)
#define TRIMANA_CORE_ERROR(...) core::loggers::log::get_core_logger()->error(__VA_ARGS__)
#define TRIMANA_CORE_CRITICAL(...) core::loggers::log::get_core_logger()->critical(__VA_ARGS__)

// Define macros for logging with the engine logger.
#define TRIMANA_TRACE(...) core::loggers::log::get_engine_logger()->trace(__VA_ARGS__)
#define TRIMANA_INFO(...) core::loggers::log::get_engine_logger()->info(__VA_ARGS__)
#define TRIMANA_WARN(...) core::loggers::log::get_engine_logger()->warn(__VA_ARGS__)
#define TRIMANA_ERROR(...) core::loggers::log::get_engine_logger()->error(__VA_ARGS__)
#define TRIMANA_CRITICAL(...) core::loggers::log::get_engine_logger()->critical(__VA_ARGS__)

#endif // __log_h__