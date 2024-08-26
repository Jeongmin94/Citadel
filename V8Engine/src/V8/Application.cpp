#include "v8pch.h"

#include "Application.h"
#include "V8/Core/Layer.h"
#include "V8/Core/LayerStack.h"
#include "V8/Core/Window.h"
#include "V8/Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace V8
{

// clang-format off
#define BIND_EVENT_FN(x) \
    std::bind(&x, this, std::placeholders::_1)

// clang-format on

Application::Application()
{
    m_Window = std::unique_ptr<IWindow>(IWindow::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    m_LayerStack = new LayerStack;
}

Application::~Application() { delete m_LayerStack; }

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
        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(
        BIND_EVENT_FN(Application::OnWindowClose));
    // dispatcher.Dispatch<WindowCloseEvent>(
    //     [&](WindowCloseEvent& e)
    //     {
    //         m_IsRunning = false;
    //         return true;
    //     });

    for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
    {
        (*--it)->OnEvent(event);
        if (event.m_isHandled)
            break;
    }

    V8_CORE_TRACE("{0}", event.ToString());
}

void Application::PushLayer(Layer* layer) { m_LayerStack->PopLayer(layer); }

void Application::PushOverlay(Layer* layer)
{
    m_LayerStack->PushOverlay(layer);
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_IsRunning = false;
    return true;
}

} // namespace V8
