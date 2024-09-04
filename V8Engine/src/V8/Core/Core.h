#pragma once

// clang-format off

#ifdef V8_PLATFORM_WINDOWS
	#ifdef V8_BUILD_DLL
		#define V8API __declspec(dllexport)
	#else
		#define V8API __declspec(dllimport)
	#endif
#else
	#error Currently V8Engine supports only Winodws!
#endif

#ifdef CITADEL_DEBUG
	#define V8_ENABLE_ASSERTS
#endif

#ifdef V8_ENABLE_ASSERTS
	#define V8_ASSERT(x, ...) if(!(x)) { V8_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}
	#define V8_CORE_ASSERT(x, ...) if(!(x)) { V8_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}
#else
	#define V8_ASSERT(x, ...)
	#define V8_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

// fn(Event)
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// clang-format on
