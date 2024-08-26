#pragma once

#include "V8/Core/Core.h"
#include "V8/Core/LayerStack.h"

#include <memory>

namespace V8
{

class IWindow;
class Event;
class WindowCloseEvent;

class Layer;

class V8API Application
{
public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& event);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<IWindow> m_Window;
    bool m_IsRunning = true;
    LayerStack m_LayerStack;
};

// DEFINED in CLIENT
Application* CreateApplication();

} // namespace V8
