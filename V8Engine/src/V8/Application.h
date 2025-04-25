#pragma once

#include "BulletFarm.h"
#include "V8/Core/Core.h"

#include <memory>

namespace V8
{

class IWindow;
class Event;
class WindowClosedEvent;

class Layer;
class LayerStack;
class ImGuiLayer;

class IShader;

class V8API Application
{

public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& event);

public:
    void Validate() const;
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    inline static Application& Get() { return *s_Instance; }
    inline IWindow& GetWindow() { return *m_Window; }

private:
    bool OnWindowClose(WindowClosedEvent& e);

    bool m_IsRunning = true;
    LayerStack* m_LayerStack = nullptr;
    ImGuiLayer* m_ImGuiLayer = nullptr;

private:
    std::unique_ptr<IWindow> m_Window;
    std::unique_ptr<IShader> m_Shader;

    uint32 m_VertexArray, m_VertexBuffer, m_IndexBuffer;

private:
    static Application* s_Instance;
};

// DEFINED in CLIENT
Application* CreateApplication();

} // namespace V8
