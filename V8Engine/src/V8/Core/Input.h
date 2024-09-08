#pragma once

#include "BulletFarm/PrimitiveTypes.h"
#include "V8/Core/Core.h"

namespace V8
{

class V8API Input
{
public:
    using MousePos = std::pair<float32, float32>;

protected:
    virtual ~Input()
    {
        if (s_Instance)
            delete s_Instance;
    }

    virtual void OnDelete() = 0;

public:
    inline static bool IsKeyPressed(int32 keycode)
    {
        return s_Instance->IsKeyPressedImpl(keycode);
    };

    inline static bool IsMouseButtonPressed(int32 button)
    {
        return s_Instance->IsMouseButtonPressedImpl(button);
    }

    inline static MousePos GetMousePos()
    {
        return s_Instance->GetMousePosImpl();
    }
    inline static float32 GetMouseX() { return s_Instance->GetMouseXImpl(); }
    inline static float32 GetMouseY() { return s_Instance->GetMouseYImpl(); }

protected:
    virtual bool IsKeyPressedImpl(int32 keycode) = 0;
    virtual bool IsMouseButtonPressedImpl(int32 button) = 0;
    virtual MousePos GetMousePosImpl() = 0;
    virtual float32 GetMouseXImpl() = 0;
    virtual float32 GetMouseYImpl() = 0;

private:
    static Input* s_Instance;
};

} // namespace V8