#pragma once

#include "Core.h"

namespace V8
{

class V8API Application
{
public:
    Application();
    virtual ~Application();

    void Run();
};

// DEFINED in CLIENT
Application* CreateApplication();

} // namespace V8
