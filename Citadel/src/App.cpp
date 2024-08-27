#include <V8Engine.h>

class CitadelSandBox : public V8::Application
{
public:
    CitadelSandBox() { PushLayer(new V8::ImGuiLayer()); }
    ~CitadelSandBox() override{};
};

V8::Application* V8::CreateApplication() { return new CitadelSandBox; }