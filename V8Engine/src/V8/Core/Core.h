#pragma once

// clang-format off

#if defined(V8_PLATFORM_WINDOWS) || defined(V8_PLATFORM_MAC)
    #ifdef V8_DYNAMIC_LINK
	#ifdef V8_BUILD_DLL
	    #define V8API __declspec(dllexport)
	#else
	    #define V8API __declspec(dllimport)
	#endif
    #else
	#define V8API
    #endif
#else
    #error Not Supported OS!
#endif

#ifdef CITADEL_DEBUG
	#define V8_ENABLE_ASSERTS
#endif

#if defined(V8_ENABLE_ASSERTS) && defined(V8_PLATFORM_WINDOWS)
	#define CLI_ASSERT(x, ...) if(!(x)) { CLI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
	#define CORE_ASSERT(x, ...) if(!(x)) { CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
	#define CLI_ASSERT(x, ...)
	#define CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

// fn(Event)
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// clang-format on
