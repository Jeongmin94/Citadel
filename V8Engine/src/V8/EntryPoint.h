#pragma once

#ifdef V8_PLATFORM_WND

extern V8::Application* V8::CreateApplication();

int main(int argc, char** argv)
{
    auto app = V8::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif