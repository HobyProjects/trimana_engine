#ifndef __base_h__
#define __base_h__

#include <memory>

#ifndef __platform_detection_h__
#include "platform_detection.hpp"
#endif

#ifdef _DEBUG
#if defined(TRIMANA_PLATFORM_WINDOWS)
#define TRIMANA_DEBUGBREAK() __debugbreak()
#elif defined(TRIMANA_PLATFORM_LINUX)
#include <signal.h>
#define TRIMANA_DEBUGBREAK() raise(SIGTAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define TRIMANA_ASSERTS_ENABLED
#else
#if defined(TRIMANA_PLATFORM_WINDOWS)
#define TRIMANA_DEBUGBREAK() 
#elif defined(TRIMANA_PLATFORM_LINUX)
#include <signal.h>
#define TRIMANA_DEBUGBREAK() 
#endif
#endif

#endif // __base_h__