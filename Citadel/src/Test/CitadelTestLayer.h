#pragma once

#include "V8/Core/Layer.h"
#include "V8/GUI/ImGuiHeader.h"

#include "Test_glm.h"

class TestLayer : public V8::Layer
{
public:
    TestLayer(const char* name) : Layer(name){};
    TestLayer() : Layer("Example")
    {
        // for glm compile test
        auto cam = camera(5.0f, {0.5f, 0.5f});
    }

    virtual void OnGUIRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!!!");
        ImGui::End();
    }

    void OnEvent(V8::Event& e) override
    {
        // CLI_TRACE("{0}", e.ToString());
    }
};