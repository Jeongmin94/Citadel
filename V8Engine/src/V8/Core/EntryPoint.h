#pragma once

#if defined(V8_PLATFORM_WINDOWS) || defined(V8_PLATFORM_MAC)

// clang-format off
#if defined(V8_PLATFORM_WINDOWS) && defined(CITADEL_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
    #include <stdlib.h>
#endif
// clang-format on

extern V8::Application* V8::CreateApplication();

int main(int argc, char** argv)
{
#if defined(V8_PLATFORM_WINDOWS) && defined(CITADEL_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(159);
#endif

    V8::Log::Init();

    CORE_WARN("Initialized V8_CORE Log!");
    CLI_WARN("Initialized CLI Log!");

    auto app = V8::CreateApplication();
    app->Validate();

    app->Run();
    delete app;

    V8::Log::Reset();

#ifdef defined(V8_PLATFORM_WINDOWS) && defined(CITADEL_DEBUG)
    // https://stackoverflow.com/questions/2323458/how-to-ignore-false-positive-memory-leaks-from-crtdumpmemoryleaks
    //_CrtDumpMemoryLeaks();
    _CrtSetBreakAlloc(159);

#endif

    return 0;
}

#else
#error This App doesn't have a _main
#endif