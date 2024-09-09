#include "v8pch.h"

#include "Application.h"
#include "V8/Core/Input.h"
#include "V8/Core/Layer.h"
#include "V8/Core/LayerStack.h"
#include "V8/Core/Window.h"
#include "V8/Events/ApplicationEvent.h"
#include "V8/Events/Event.h"
#include "V8/GUI/ImGuiLayer.h"

#include "Platform/Windows/WindowsInput.h"

#include <glad/glad.h>

namespace V8
{

Application* Application::s_Instance = nullptr;

Application::Application()
{
    CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<IWindow>(IWindow::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    m_LayerStack = new LayerStack;
    m_ImGuiLayer = new ImGuiLayer;
    PushLayer(m_ImGuiLayer);
}

Application::~Application()
{
    if (m_LayerStack)
        delete m_LayerStack;

    Input::Get().OnDestroy();
}

void Application::Run()
{
    while (m_IsRunning)
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer* layer : *m_LayerStack)
        {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : *m_LayerStack)
        {
            layer->OnGUIRender();
        }
        m_ImGuiLayer->End();

        auto [x, y] = Input::GetMousePos();
        CORE_TRACE("{0}, {1}", x, y);

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    // Application level event
    // event.SetIsHandled(m_HandlerRegistry->HandleEvent(event));
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowClosedEvent>(
        BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
    {
        (*--it)->OnEvent(event);
        if (event.IsHandled())
            break;
    }

    CORE_TRACE("{0}", event.ToString());
}

void Application::PushLayer(Layer* layer)
{
    m_LayerStack->PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
    m_LayerStack->PushOverlay(layer);
    layer->OnAttach();
}

bool Application::OnWindowClose(WindowClosedEvent& e)
{
    m_IsRunning = false;
    return true;
}

} // namespace V8
