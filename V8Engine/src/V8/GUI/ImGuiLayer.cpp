#include "v8pch.h"

#include "ImGuiLayer.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <imgui.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "V8/Application.h"
#include "V8/Core/Window.h"
#include "V8/Events/Event.h"

namespace V8
{
ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{
    // m_HandlerRegistry = std::make_shared<EventHandlerRegistry>();

    // m_HandlerRegistry->RegisterHandler<MouseButtonPressedEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    // m_HandlerRegistry->RegisterHandler<MouseButtonReleasedEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    // m_HandlerRegistry->RegisterHandler<MouseMovedEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    // m_HandlerRegistry->RegisterHandler<MouseScrolledEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

    // m_HandlerRegistry->RegisterHandler<KeyPressedEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    // m_HandlerRegistry->RegisterHandler<KeyReleasedEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    // m_HandlerRegistry->RegisterHandler<KeyTypedEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

    // m_HandlerRegistry->RegisterHandler<WindowResizedEvent>(
    //     BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
}

ImGuiLayer::~ImGuiLayer() {}

// ref: ImGui/examples/example_glfw_opengl3/main.cpp
void ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

    io.FontGlobalScale = 2.0f;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Application& app = Application::Get();
    GLFWwindow* window =
        static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    CORE_INFO("ImGui Version: {0}", IMGUI_VERSION);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    // clang-format off
    //io.KeyMap[ImGuiKey_Tab]             = GLFW_KEY_TAB;
    //io.KeyMap[ImGuiKey_LeftArrow]       = GLFW_KEY_LEFT;
    //io.KeyMap[ImGuiKey_RightArrow]      = GLFW_KEY_RIGHT;
    //io.KeyMap[ImGuiKey_UpArrow]         = GLFW_KEY_UP;
    //io.KeyMap[ImGuiKey_DownArrow]       = GLFW_KEY_DOWN;
    //io.KeyMap[ImGuiKey_PageUp]          = GLFW_KEY_PAGE_UP;
    //io.KeyMap[ImGuiKey_PageDown]        = GLFW_KEY_PAGE_DOWN;
    //io.KeyMap[ImGuiKey_Home]            = GLFW_KEY_HOME;
    //io.KeyMap[ImGuiKey_End]             = GLFW_KEY_END;
    //io.KeyMap[ImGuiKey_Insert]          = GLFW_KEY_INSERT;
    //io.KeyMap[ImGuiKey_Delete]          = GLFW_KEY_DELETE;
    //io.KeyMap[ImGuiKey_Backspace]       = GLFW_KEY_BACKSPACE;
    //io.KeyMap[ImGuiKey_Space]           = GLFW_KEY_SPACE;
    //io.KeyMap[ImGuiKey_Enter]           = GLFW_KEY_ENTER;
    //io.KeyMap[ImGuiKey_Escape]          = GLFW_KEY_ESCAPE;
    //io.KeyMap[ImGuiKey_A]               = GLFW_KEY_A;
    //io.KeyMap[ImGuiKey_C]               = GLFW_KEY_C;
    //io.KeyMap[ImGuiKey_V]               = GLFW_KEY_V;
    //io.KeyMap[ImGuiKey_X]               = GLFW_KEY_X;
    //io.KeyMap[ImGuiKey_Y]               = GLFW_KEY_Y;
    //io.KeyMap[ImGuiKey_Z]               = GLFW_KEY_Z;
    // clang-format on
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // glfwTerminate(); this must be called when the last glfwWindow's closing!
}

void ImGuiLayer::OnGUIRender()
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

void ImGuiLayer::OnEvent(Event& e)
{
    // CORE_INFO("{0}", e.StaticType().ToString());
    // CORE_INFO("{0}", e.GetType().ToString());

    // e.SetIsHandled(m_HandlerRegistry->HandleEvent(e));
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),
                            (float)app.GetWindow().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

// !TODO: MouseCodeMapper ���
bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;

    return false;
}
// !TODO: MouseCodeMapper ���
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