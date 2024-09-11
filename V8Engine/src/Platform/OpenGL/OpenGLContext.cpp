#include "v8pch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace V8
{

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle)
{
    CORE_ASSERT(windowHandle, "Window Handle is null!");
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    CORE_ASSERT(status, "Failed to initialize Glad!");

    CORE_INFO("OpenGL Info:");
    CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
    CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
    CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers()
{
    // glBegin(GL_TRIANGLES);
    // glEnd();

    glfwSwapBuffers(m_WindowHandle);
}
} // namespace V8