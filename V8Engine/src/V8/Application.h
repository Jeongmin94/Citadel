#pragma once

#include "Core.h"
#include "Window.h"

namespace V8
{

class V8API Application
{
public:
    Application();
    virtual ~Application();

    void Run();

private:
    std::unique_ptr<IWindow> m_Window;
    bool m_Running = true;
};

// DEFINED in CLIENT
Application* CreateApplication();

} // namespace V8
