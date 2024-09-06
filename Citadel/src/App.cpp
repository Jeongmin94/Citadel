#include <V8Engine.h>

class ExampleLayer : public V8::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {
        //CLI_INFO("{0}", "ExampleLayer::Update");

        if (V8::Input::IsKeyPressed(V8::Key::Tab))
        {
            CLI_TRACE("{0}", "Tab key is pressed!");
        }
    }

    void OnEvent(V8::Event& e) override
    { 
        //CLI_TRACE("{0}", e.ToString());
    }
};

class CitadelSandBox : public V8::Application
{
public:
    CitadelSandBox()
    {
        PushLayer(new V8::ImGuiLayer());
        PushLayer(new ExampleLayer());
    }
    ~CitadelSandBox() override{};
};

V8::Application* V8::CreateApplication() { return new CitadelSandBox; }