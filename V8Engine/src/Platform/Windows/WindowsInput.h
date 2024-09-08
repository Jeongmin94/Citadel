#pragma once

#include "V8/Core/Input.h"

namespace V8
{

class WindowsInput : public Input
{
protected:
    virtual ~WindowsInput() override;

protected:
    virtual bool IsKeyPressedImpl(int32 keycode) override;
    virtual bool IsMouseButtonPressedImpl(int32 button) override;
    virtual MousePos GetMousePosImpl() override;
    virtual float32 GetMouseXImpl() override;
    virtual float32 GetMouseYImpl() override;
};

} // namespace V8