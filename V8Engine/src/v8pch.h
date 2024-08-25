#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <stdint.h>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "V8/Utils/Log.h"

// clang-format off

#ifdef V8_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

using uint32	= uint32_t;
using uint16	= uint16_t;
using uint8		= uint8_t;

using int32		= int32_t;
using int16		= int16_t;
using int8		= int8_t;

using float32	= float;
using float64	= double;

// clang-format on