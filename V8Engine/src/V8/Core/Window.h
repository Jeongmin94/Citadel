#pragma once

#include "V8/Core/Core.h"
#include "V8/Events/Event.h"

namespace V8
{

/*
 * Abstract Window Layer
 */

struct WindowProps
{
    std::string Title;
    uint32 Width;
    uint32 Height;

    WindowProps(const std::string& title = "Citadel Engine",
                uint32 width = 2400, uint32 height = 1440)
        : Title(title), Width(width), Height(height){};
};

// Interface representing a pc system based Window
class V8API IWindow
{
public:
    virtual ~IWindow(){};

    virtual void OnUpdate() = 0;

    virtual uint32 GetWidth() const = 0;
    virtual uint32 GetHeight() const = 0;

    // Window Attributes
    virtual void SetEventCallback(const EventCallbackVoidFn& callback) = 0;
    virtual void SetVSync(bool isEnabled) = 0;
    virtual bool IsVSync() const = 0;

    // return type is void*, for support any other gui window
    virtual void* GetNativeWindow() const = 0;

    // implementation of this functions is defined in IWindow's implementation
    static IWindow* Create(const WindowProps& props = WindowProps());
};
} // namespace V8