#include <BulletFarm.h>

#include <V8Engine.h>

#ifdef CITADEL_DEBUG
#include "Test/CitadelTestLayer.h"
#endif

// TODO: add configuration management

class CitadelSandBox : public V8::Application
{
public:
    CitadelSandBox()
    {
#ifdef CITADEL_DEBUG
        std::stringstream ss;
        for (int i = 0; i < 3; i++)
        {
            ss << "TestLayer" << i;
            PushLayer(new TestLayer(ss.str().c_str()));
            ss.str(std::string());
        }
#endif
    }

    ~CitadelSandBox() override = default;
};

V8::Application* V8::CreateApplication() { return new CitadelSandBox; }