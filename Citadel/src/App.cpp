#include <V8Engine.h>

class CitadelSandBox : public V8::Application
{
public:
    CitadelSandBox() {}
    ~CitadelSandBox() override{};
};

V8::Application* V8::CreateApplication() { return new CitadelSandBox; }