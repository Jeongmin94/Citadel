#include "v8pch.h"

#include "Application.h"
#include <GLFW/glfw3.h>

namespace V8
{

Application::Application()
{
    //m_Window = std::make_unique<IWindow>(IWindow::Create());
    m_Window = std::unique_ptr<IWindow>(IWindow::Create());
}

Application::~Application() {}

void Application::Run()
{
    while (m_Running)
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Window->OnUpdate();
    }
}

} // namespace V8
