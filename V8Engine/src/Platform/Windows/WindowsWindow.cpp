#include "v8pch.h"

#include "WindowsWindow.h"

namespace V8
{

static bool s_GLFWInitialized = false;

IWindow* IWindow::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }

WindowsWindow::~WindowsWindow() { Shutdown(); }

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void WindowsWindow::SetVSync(bool isEnabled)
{
    if (isEnabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
    m_Data.VSync = isEnabled;
}

bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

void WindowsWindow::Init(const WindowProps& props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    V8_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
                 props.Height);

    if (!s_GLFWInitialized)
    {
        // !TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        V8_CORE_ASSERT(success, "Could not be initialize GLFW!");

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((uint32)props.Width, (uint32)props.Height,
                                m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
}

void WindowsWindow::Shutdown() { glfwDestroyWindow(m_Window); }

} // namespace V8