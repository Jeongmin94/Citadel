#include <V8Engine.h>

#include "ImGui-Docking/imgui.h"

#include "Test_glm.h"

class TestLayer : public V8::Layer
{
public:
    TestLayer(const char* name) : Layer(name){};
    TestLayer() : Layer("Example") { auto cam = camera(5.0f, {0.5f, 0.5f}); }

    virtual void OnGUIRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }

    void OnEvent(V8::Event& e) override
    {
        // CLI_TRACE("{0}", e.ToString());
    }
};

class CitadelSandBox : public V8::Application
{
public:
    CitadelSandBox()
    {
        std::stringstream ss;
        for (int i = 0; i < 3; i++)
        {
            ss << "TestLayer" << i;
            PushLayer(new TestLayer(ss.str().c_str()));
            ss.str(std::string());
        }
    }
    ~CitadelSandBox() override{};
};

V8::Application* V8::CreateApplication() { return new CitadelSandBox; }