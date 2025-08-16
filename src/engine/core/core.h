#pragma once

#include <memory>

#include "engine/core/Log.h"

#ifdef _WIN32
	#ifdef _WIN64
		#define EG_PLATFORM_WINDOWS
	#else
		#error "Unsupported Windows platform"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
		#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Sim not supported"
	#elif TARGET_OS_IPHONE == 1
		#define EG_PLATFORM_IOS
		#error "IOS not supported"
	#elif TARGET_OS_MAC == 1
        #define EG_PLATFORM_MACOS
        #if TARGET_CPU_ARM64
            #define EG_PLATFORM_MACOS_ARM64
            #error "MacOS not supported"
        #elif TARGET_CPU_X86_64
            #define EG_PLATFORM_MACOS_x86
            #error "MacOS not supported"
        #else
            #error "Unknown Mac architecture!"
        #endif
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define EG_PLATFORM_ANDROID
	#error "Android not supported"
#elif defined(__linux__)
	#define EG_PLATFORM_LINUX
	#error "Linux not supported"
#else
	#error "What kind of platform are you using? What ever it is it's not supported"
#endif

#define EG_ENABLE_ASSERTS
#ifdef EG_DEBUG
    #if defined(EG_PLATFORM_WINDOWS)
        #define EG_DEBUGBREAK() __debugbreak()
    #elif defined(EG_PLATFORM_LINUX)
        #include <signal.h>
        #define EG_DEBUGBREAK() raise(SIGTRAP)
    #elif defined(EG_PLATFORM_MACOS_x86)
        #define EG_DEBUGBREAK() __asm__ volatile("int $0x03")
    #elif defined(EG_PLATFORM_MACOS_ARM64)
        #define EG_DEBUGBREAK() __builtin_trap()
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
#else
	#define EG_DEBUGBREAK()
#endif

#ifdef EG_ENABLE_ASSERTS
#define EG_ASSERT(x, ...) { if(!(x)) { EG_ERROR("Assertion Failed: {0}", __VA_ARGS__); EG_DEBUGBREAK(); } }
#define EG_CORE_ASSERT(x, ...) { if(!(x)) { EG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); EG_DEBUGBREAK(); } }
#else
#define EG_ASSERT(x, ...)
#define EG_CORE_ASSERT(x, ...)
#endif

namespace Engine {

	template<typename T>
	// Just making it easier to create unique pointers
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	// Just making it easier to create shared pointers
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}