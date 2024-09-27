#pragma once

#include "V8/Core/Window.h"

#include "V8/Renderer/IGraphicsContext.h"

namespace V8
{

class V8API MacWindow: public IWindow
{
public:
    MacWindow(const WindowProps& props);
    virtual ~MacWindow() override;

public:
    void OnUpdate() override;

    inline uint32 GetWidth() const override { return 0; };
    inline uint32 GetHeight() const override { return 0; };

    inline void SetEventCallback(const EventCallbackVoidFn& callback) override
    {
        // m_Data.EventCallback = callback;
    }
    void SetVSync(bool isEnabled) override;
    bool IsVSync() const override;

    inline void* GetNativeWindow() const override { return nullptr; }
};


}