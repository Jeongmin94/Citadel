#include "v8pch.h"

#include "Application.h"
#include "V8/Core/Input.h"
#include "V8/Core/Layer.h"
#include "V8/Core/LayerStack.h"
#include "V8/Core/Window.h"
#include "V8/Events/ApplicationEvent.h"
#include "V8/Events/Event.h"
#include "V8/GUI/ImGuiLayer.h"
#include "V8/Renderer/IShader.h"

#include "Platform/Windows/WindowsInput.h"

#include <glad/glad.h>

namespace V8
{

Application* Application::s_Instance = nullptr;

Application::Application()
{
    CORE_INFO("Application Initializing");

    CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<IWindow>(IWindow::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    m_LayerStack = new LayerStack;
    m_ImGuiLayer = new ImGuiLayer;
    PushOverlay(m_ImGuiLayer);

    CORE_INFO("Application Initializing Finished");

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    float32 vertices[3 * 3] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                               0.0f,  0.0f,  0.5f, 0.0f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float32),
                          nullptr);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    uint32 indices[3] = {0, 1, 2};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        out vec3 v_Position;
        
        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        
        void main()
        {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
        }
    )";

    m_Shader = std::make_unique<IShader>(vertexSrc, fragmentSrc);
}

Application::~Application()
{
    if (m_LayerStack)
        delete m_LayerStack;

    Input::Get().OnDestroy();
}

void Application::Run()
{
    while (m_IsRunning)
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();

        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        m_Shader->UnBind();

        for (Layer* layer : *m_LayerStack)
        {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : *m_LayerStack)
        {
            layer->OnGUIRender();
        }
        m_ImGuiLayer->End();

        // auto [x, y] = Input::GetMousePos();
        // CORE_TRACE("{0}, {1}", x, y);

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    // Application level event
    // event.SetIsHandled(m_HandlerRegistry->HandleEvent(event));
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowClosedEvent>(
        BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
    {
        (*--it)->OnEvent(event);
        if (event.IsHandled())
            break;
    }

    // CORE_TRACE("{0}", event.ToString());
}

void Application::Validate() const
{
    CORE_ASSERT(m_LayerStack, "LayerStack is nullptr");
    CORE_INFO("{0}", m_LayerStack->ToString());
}

void Application::PushLayer(Layer* layer)
{
    m_LayerStack->PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
    m_LayerStack->PushOverlay(layer);
    layer->OnAttach();
}

bool Application::OnWindowClose(WindowClosedEvent& e)
{
    m_IsRunning = false;
    return true;
}

} // namespace V8
