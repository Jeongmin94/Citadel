#include "v8pch.h"

#include "ImGuiLayer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "V8/Application.h"
#include "V8/Core/Core.h"
#include "V8/Core/Window.h"
#include "V8/Events/Event.h"

namespace V8
{
ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{
    m_HandlerRegistry = std::make_shared<EventHandlerRegistry>();

    m_HandlerRegistry->RegisterHandler<MouseButtonPressedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    m_HandlerRegistry->RegisterHandler<MouseButtonReleasedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    m_HandlerRegistry->RegisterHandler<MouseMovedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    m_HandlerRegistry->RegisterHandler<MouseScrolledEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

    m_HandlerRegistry->RegisterHandler<KeyPressedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    m_HandlerRegistry->RegisterHandler<KeyReleasedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    m_HandlerRegistry->RegisterHandler<KeyTypedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

    m_HandlerRegistry->RegisterHandler<WindowResizedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
}

ImGuiLayer::~ImGuiLayer() {}

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

    CORE_INFO("ImGui Version: {0}", IMGUI_VERSION);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    // glfwTerminate(); this must be called when the last glfwWindow's closing!
}

void ImGuiLayer::OnUpdate()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float32)app.GetWindow().GetWidth(),
                            (float32)app.GetWindow().GetHeight());

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

void ImGuiLayer::OnEvent(Event& e)
{
    CORE_INFO("{0}", e.StaticType().ToString());
    CORE_INFO("{0}", e.GetType().ToString());

    e.SetIsHandled(m_HandlerRegistry->HandleEvent(e));
}

// !TODO: MouseCodeMapper 사용
bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;

    return false;
}
// !TODO: MouseCodeMapper 사용
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
    int32 platformCode = e.GetPlatformCode();

    ImGuiIO& io = ImGui::GetIO();

    io.KeysDown[platformCode] = true;

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
    int32 platformCode = e.GetPlatformCode();

    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[platformCode] = false;
    return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
{
    int32 platformCode = e.GetPlatformCode();

    ImGuiIO& io = ImGui::GetIO();
    if (platformCode > 0 && platformCode < 0x10000)
    {
        io.AddInputCharacter(platformCode);
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