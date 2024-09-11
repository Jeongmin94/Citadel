#pragma once

#include "V8/Core/Window.h"

#include "V8/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace V8
{

class V8API WindowsWindow : public IWindow
{
public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void OnUpdate() override;

    inline uint32 GetWidth() const override { return m_Data.Width; };
    inline uint32 GetHeight() const override { return m_Data.Height; };

    inline void SetEventCallback(const EventCallbackVoidFn& callback) override
    {
        m_Data.EventCallback = callback;
    }
    void SetVSync(bool isEnabled) override;
    bool IsVSync() const override;

    inline void* GetNativeWindow() const override { return m_Window; }

private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

private:
    void SetWindowCallbacks(GLFWwindow* titleWindow);

private:
    GLFWwindow* m_Window;
    GraphicsContext* m_Context;

    struct WindowData
    {
        std::string Title;
        uint32 Width, Height;
        bool VSync;

        EventCallbackVoidFn EventCallback;
    };

    WindowData m_Data;
};

} // namespace V8
