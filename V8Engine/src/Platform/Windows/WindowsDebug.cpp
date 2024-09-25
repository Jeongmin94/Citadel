#include "v8pch.h"

#include "WindowsDebug.h"

namespace V8
{

void WindowsDebug::IncludeDebugHeader()
{
    // clang-format off
#if defined(V8_PLATFORM_WINDOWS) && defined(CITADEL_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
    #include <stdlib.h>
#endif
    // clang-format on
}

void WindowsDebug::InitDebug()
{
#if defined(V8_PLATFORM_WINDOWS) && defined(CITADEL_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(159);
#endif
}

void WindowsDebug::CatchDebug()
{
#ifdef defined(V8_PLATFORM_WINDOWS) && defined(CITADEL_DEBUG)
    // https://stackoverflow.com/questions/2323458/how-to-ignore-false-positive-memory-leaks-from-crtdumpmemoryleaks
    //_CrtDumpMemoryLeaks();
    _CrtSetBreakAlloc(159);
#endif
}

} // namespace V8
