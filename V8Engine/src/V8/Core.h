#pragma once

#ifdef V8_PLATFORM_WND
	#ifdef V8_BUILD_DLL
		#define V8API __declspec(dllexport)
	#else
		#define V8API __declspec(dllimport)
	#endif
#else
	#error Currently V8Engine supports only Winodws!
#endif
