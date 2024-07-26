#ifndef __assert_h__
#define __assert_h__

#include <filesystem>
#include <cassert>

#include "log.hpp"
#include "base.hpp"

// The following block defines the TRIMANA_ASSERT macro. This macro is used to check if a given expression is true.
// If the expression is true, nothing happens. If the expression is false, an error message is printed to the console
// indicating the location of the assertion and the assertion message. The macro also triggers a debug breakpoint.

// The macro is only defined if the TRIMANA_ASSERTS_ENABLED flag is defined. This flag is typically defined in a project's
// build configuration to enable assertions in debug builds and disable them in release builds.

#ifdef TRIMANA_ASSERTS_ENABLED

// Define the TRIMANA_ASSERT macro
#define TRIMANA_ASSERT(expression, ...)                                                                                                \
    if ((expression))                                                                                                                  \
    {                                                                                                                                  \
        TRIMANA_CORE_ERROR("Assertion failed ({0}|{1}):", std::filesystem::path(__FILE__).filename().string(), __LINE__, __VA_ARGS__); \
        TRIMANA_DEBUGBREAK();                                                                                                          \
    }
#else

// If TRIMANA_ASSERTS_ENABLED is not defined, define the TRIMANA_ASSERT macro to do nothing
#define TRIMANA_ASSERT(expression, ...)

#endif

#endif // __assert_h__