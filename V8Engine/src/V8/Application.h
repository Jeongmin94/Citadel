#pragma once

#include "V8/Core/Core.h"

#include <memory>

namespace V8
{

class IWindow;
class Event;
class WindowCloseEvent;

class Layer;
class LayerStack;

class V8API Application
{
public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& event);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    inline static Application& Get() { return *s_Instance; }
    inline IWindow& GetWindow() { return *m_Window; }

private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<IWindow> m_Window;
    bool m_IsRunning = true;
    LayerStack* m_LayerStack = nullptr;

    static Application* s_Instance;
};

// DEFINED in CLIENT
Application* CreateApplication();

} // namespace V8
