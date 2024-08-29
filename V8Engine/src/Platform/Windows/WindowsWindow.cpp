#include "v8pch.h"

#include "V8/Events/ApplicationEvent.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace V8
{
/*
 * TODO: support DirectX and Win32API
 */

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* desc)
{
    V8_CORE_ERROR("GLFW Error ({0}): {1}", error, desc);
}

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

        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((uint32)props.Width, (uint32)props.Height,
                                m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    V8_CORE_ASSERT(status, "Failed to initialize Glad!");
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(
        m_Window,
        [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizedEvent event(width, height);
            data.EventCallback(event);
        });

    glfwSetWindowCloseCallback(
        m_Window,
        [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowClosedEvent event;
            data.EventCallback(event);
        });
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);

    // !TODO: glfwTerminate must be called when all glfw window are closed
    glfwTerminate();
}

} // namespace V8