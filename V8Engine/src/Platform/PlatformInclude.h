#pragma once

#ifdef V8_PLATFORM_WINDOWS
#include "Platform/Windows/include/WindowsInclude.h"
#elif V8_PLATFORM_MAC
#include "Platform/Mac/include/MacInclude.h"
#endif