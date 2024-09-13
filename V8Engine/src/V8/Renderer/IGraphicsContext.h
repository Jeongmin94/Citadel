#pragma once

namespace V8
{

// Interface for Graphics Context
class IGraphicsContext
{
public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};

} // namespace V8