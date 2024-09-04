#include "v8pch.h"

#include "ImGuiLayer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "V8/Application.h"
#include "V8/Core/Core.h"
#include "V8/Core/Window.h"

namespace V8
{
ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    // glfwTerminate(); this must be called when the last glfwWindow's closing!
}

// ref: ImGui/examples/example_glfw_opengl3/main.cpp
void ImGuiLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // clang-format off
    io.KeyMap[ImGuiKey_Tab]             = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow]       = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow]      = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow]         = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow]       = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp]          = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown]        = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home]            = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End]             = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert]          = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete]          = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace]       = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space]           = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter]           = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape]          = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A]               = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C]               = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V]               = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X]               = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y]               = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z]               = GLFW_KEY_Z;
    // clang-format on

    V8_CORE_INFO("ImGui Version: {0}", IMGUI_VERSION);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),
                            (float)app.GetWindow().GetHeight());

    float32 time = (float32)glfwGetTime();
    io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

std::unordered_map<Type, std::function<void(Event&)>> funcMap;

void ImGuiLayer::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<MouseMovedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));

    dispatcher.Dispatch<MouseButtonPressedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));

    dispatcher.Dispatch<MouseButtonReleasedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;

    return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = false;

    return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.GetX(), e.GetY());

    return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e.GetOffsetX();
    io.MouseWheel += e.GetOffsetY();

    return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.GetKeyCode()] = true;

    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                 io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift =
        io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt =
        io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper =
        io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.GetKeyCode()] = false;
    return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    V8::KeyCode keycode = e.GetKeyCode();
    if (keycode > 0 && keycode < 0x10000)
    {
        io.AddInputCharacter(keycode);
    }

    return false;
}

bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e.GetWidth(), e.GetHeight());

    return false;
}

} // namespace V8