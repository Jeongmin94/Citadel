#pragma once

#ifdef V8_PLATFORM_WINDOWS

// clang-format off
#ifdef CITADEL_DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
    #include <stdlib.h>
#endif
// clang-format on

extern V8::Application* V8::CreateApplication();

int main(int argc, char** argv)
{
#ifdef CITADEL_DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//_CrtSetBreakAlloc(1039);
#endif

    V8::Log::Init();

    V8_CORE_WARN("Initialized Log!");
    CLI_DEBUG("Hello Var = {0}", 10);

    auto app = V8::CreateApplication();
    app->Run();
    delete app;

    V8::Log::Reset();

#ifdef CITADEL_DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}

#endif