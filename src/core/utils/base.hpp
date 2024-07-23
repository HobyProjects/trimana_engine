#ifndef __base_h__
#define __base_h__

#include <memory>

#ifndef __platform_detection_h__
#include "platform_detection.hpp"
#endif

#ifdef _DEBUG
    #if defined(TRIMANA_PLATFORM_WINDOWS)
        // Define TRIMANA_DEBUGBREAK macro for Windows platform to trigger a debug break
        #define TRIMANA_DEBUGBREAK() __debugbreak()
    #elif defined(TRIMANA_PLATFORM_LINUX)
        // Define TRIMANA_DEBUGBREAK macro for Linux platform to raise a SIGTRAP signal
        #include <signal.h>
        #define TRIMANA_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    // Define TRIMANA_ASSERTS_ENABLED for debug mode
    #define TRIMANA_ASSERTS_ENABLED
#else
    #if defined(TRIMANA_PLATFORM_WINDOWS)
        // Define TRIMANA_DEBUGBREAK macro for Windows platform in release mode
        #define TRIMANA_DEBUGBREAK() 
    #elif defined(TRIMANA_PLATFORM_LINUX)
        // Define TRIMANA_DEBUGBREAK macro for Linux platform in release mode
        #include <signal.h>
        #define TRIMANA_DEBUGBREAK() 
    #endif
#endif

#endif // __base_h__