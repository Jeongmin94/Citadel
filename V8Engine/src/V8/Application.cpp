#include "v8pch.h"

#include "Application.h"
#include "V8/Events/ApplicationEvent.h"
#include "V8/Core/Window.h"

#include <GLFW/glfw3.h>

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
}

Application::~Application() {}

void Application::Run()
{
    while (m_IsRunning)
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(
        [&](WindowCloseEvent& e)
        {
            m_IsRunning = false;
            return true;
        });

    V8_CORE_TRACE("{0}", event.ToString());
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_IsRunning = false;
    return true;
}

} // namespace V8
