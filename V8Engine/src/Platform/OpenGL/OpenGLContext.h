#pragma once

#include "V8/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace V8
{

class OpenGLContext : public GraphicsContext
{
public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;

private:
    GLFWwindow* m_WindowHandle;
};

} // namespace V8