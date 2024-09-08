#include "v8pch.h"

#include "V8/Application.h"
#include "V8/Core/Window.h"
#include "V8/Events/Codes/KeyCode.h"
#include "V8/Events/Codes/MouseCode.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

namespace V8
{
Input* Input::s_Instance = new WindowsInput;

WindowsInput::~WindowsInput() { OnDelete(); }

void WindowsInput::OnDelete(){};

bool WindowsInput::IsKeyPressedImpl(int32 keycode)
{
    auto window = static_cast<GLFWwindow*>(
        Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int32 button)
{
    auto window = static_cast<GLFWwindow*>(
        Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);

    return state == GLFW_PRESS;
}

Input::MousePos WindowsInput::GetMousePosImpl()
{
    auto window = static_cast<GLFWwindow*>(
        Application::Get().GetWindow().GetNativeWindow());
    float64 xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float32)xpos, (float32)ypos};
}

float32 WindowsInput::GetMouseXImpl() { return GetMousePosImpl().first; }

float32 WindowsInput::GetMouseYImpl() { return GetMousePosImpl().second; }

} // namespace V8