#pragma once

#ifdef V8_PLATFORM_WINDOWS

extern V8::Application* V8::CreateApplication();

int main(int argc, char** argv)
{
    V8::Log::Init();

    V8_CORE_WARN("Initialized Log!");
    CLI_DEBUG("Hello Var = {0}", 10);

    auto app = V8::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif