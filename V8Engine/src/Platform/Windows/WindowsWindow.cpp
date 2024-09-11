#include "v8pch.h"

#include "V8/Events/ApplicationEvent.h"
#include "V8/Events/Codes/KeyCode.h"
#include "V8/Events/Codes/MouseCode.h"
#include "V8/Events/KeyEvent.h"
#include "V8/Events/MouseEvent.h"
#include "WindowsWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"

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
    CORE_ERROR("GLFW Error ({0}): {1}", error, desc);
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

    m_Context->SwapBuffers();
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

    CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
              props.Height);

    if (!s_GLFWInitialized)
    {
        // !TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        CORE_ASSERT(success, "Could not be initialize GLFW!");

        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((uint32)props.Width, (uint32)props.Height,
                                m_Data.Title.c_str(), nullptr, nullptr);

    // !TODO: delete m_Context
    m_Context = new OpenGLContext(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
    SetWindowCallbacks(m_Window);
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);

    // !TODO: glfwTerminate must be called when all glfw window are closed
    glfwTerminate();

    if (m_Context)
        delete m_Context;
}

void WindowsWindow::SetWindowCallbacks(GLFWwindow* titleWindow)
{
    // Set GLFW callbacks
    glfwSetWindowSizeCallback(
        titleWindow,
        [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizedEvent event(width, height);
            data.EventCallback(event);
        });

    glfwSetWindowCloseCallback(
        titleWindow,
        [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowClosedEvent event;
            data.EventCallback(event);
        });

    glfwSetKeyCallback(
        titleWindow,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, false);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetCharCallback(titleWindow,
                        [](GLFWwindow* window, unsigned int keycode)
                        {
                            WindowData& data =
                                *(WindowData*)glfwGetWindowUserPointer(window);
                            KeyTypedEvent event(keycode);
                            data.EventCallback(event);
                        });

    glfwSetMouseButtonCallback(
        titleWindow,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetScrollCallback(
        titleWindow,
        [](GLFWwindow* window, double offsetX, double offsetY)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float32)offsetX, (float32)offsetY);
            data.EventCallback(event);
        });

    glfwSetCursorPosCallback(
        titleWindow,
        [](GLFWwindow* window, double posX, double posY)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float32)posX, (float32)(posY));
            data.EventCallback(event);
        });
}

} // namespace V8