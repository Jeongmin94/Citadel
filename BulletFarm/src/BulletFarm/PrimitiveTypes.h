#pragma once

// clang-format off

#include <cstdint>

#ifdef V8_PLATFORM_WINDOWS
    // for Windows
#elif V8_PLATFORM_MAC
    // for Mac
    #include <cstddef>
#endif

using uint32	        = uint32_t;
using uint16	        = uint16_t;
using uint8		= uint8_t;

using int32		= int32_t;
using int16		= int16_t;
using int8		= int8_t;

using float32	        = float;
using float64	        = double;

using TypeHash          = size_t;

// clang-format on