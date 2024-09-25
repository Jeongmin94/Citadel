#pragma once

#if defined(V8_PLATFORM_WINDOWS) || defined(V8_PLATFORM_MAC)

extern V8::Application* V8::CreateApplication();

int main(int argc, char** argv)
{
    // Init Log
    V8::Log::Init();

    CORE_WARN("Initialized V8_CORE Log!");
    CLI_WARN("Initialized CLI Log!");

    // Init Service
    auto locator = V8::ServiceLocatorHelper::Get();
    V8::ServiceLocatorHelper::InitLocator(locator);

    const auto debugService = locator->Get<V8::IDebug>();
    {
        debugService->IncludeDebugHeader();
        debugService->InitDebug();
    }

    auto app = V8::CreateApplication();
    app->Validate();

    app->Run();
    delete app;

    V8::Log::Reset();
    locator->Clear();

    {
        debugService->CatchDebug();
    }

    return 0;
}

#else

#error This App doesn't have a _main

#endif