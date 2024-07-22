#ifndef __assert_h__
#define __assert_h__

#include <filesystem>
#include <cassert>

#ifndef __base_h__
#include "base.hpp"
#endif

#ifdef TRIMANA_ASSERTS_ENABLED
#define TRIMANA_ASSERT(expression, ...)                                                                                                \
    if ((expression))                                                                                                                  \
    {                                                                                                                                  \
        TRIMANA_CORE_ERROR("Assertion failed ({0}|{1}):", std::filesystem::path(__FILE__).filename().string(), __LINE__, __VA_ARGS__); \
        TRIMANA_DEBUGBREAK();                                                                                                          \
    }
#else
#define TRIMANA_ASSERT(expression, ...)
#endif

#endif // __assert_h__