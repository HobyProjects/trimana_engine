#ifndef __platform_detection_h__
#define __platform_detection_h__

#if defined(_WIN32) || defined(_WIN64)
    // Define platform as Windows
    #define TRIMANA_PLATFORM_WINDOWS

    #ifdef TRIMANA_BUILD_SHARED
        // Export symbols when building shared library
        #define TRIMANA_CORE_API __declspec(dllexport)
    #else
        // Import symbols when building static library
        #define TRIMANA_CORE_API __declspec(dllimport)
    #endif

    // Define empty TRIMANA_CORE_API if not building shared library
    #ifndef TRIMANA_BUILD_SHARED
        #define TRIMANA_CORE_API 
    #endif 

#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    
    // Check for Apple platforms
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define TRIMANA_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        // Define platform as MacOS
        #define TRIMANA_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown Apple platform!"
    #endif

    // Check for Android platform
    #elif defined(__ANDROID__)
        #define TRIMANA_PLATFORM_ANDROID

    // Check for Linux platform
    #elif defined(__linux__)
        #define TRIMANA_PLATFORM_LINUX
        __attribute__((visibility("default")))
    #else
        // Unknown platform detected
        #error "Unknown platform!"
    #endif

#endif // __platform_detection_h__