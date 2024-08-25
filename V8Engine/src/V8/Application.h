#pragma once

#include "V8/Core/Core.h"

#include <memory>

namespace V8
{

class IWindow;
class Event;
class WindowCloseEvent;

class V8API Application
{
public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& event);

private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<IWindow> m_Window;
    bool m_IsRunning = true;
};

// DEFINED in CLIENT
Application* CreateApplication();

} // namespace V8
