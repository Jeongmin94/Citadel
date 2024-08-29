#pragma once

#include "V8/Core/Layer.h"
#include "V8/Events/ApplicationEvent.h"
#include "V8/Events/KeyEvent.h"
#include "V8/Events/MouseEvent.h"

namespace V8
{
class V8API ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    virtual ~ImGuiLayer() override;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnEvent(Event& e) override;

private:
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool OnMouseMovedEvent(MouseMovedEvent& e);
    bool OnMouseScrolledEvent(MouseScrolledEvent& e);

    bool OnKeyPressedEvent(KeyPressedEvent& e);
    bool OnKeyReleasedEvent(KeyReleasedEvent& e);
    bool OnKeyTypedEvent(KeyTypedEvent& e);

    bool OnWindowResizedEvent(WindowResizedEvent& e);

private:
    float32 m_Time = 0.0f;
};
} // namespace V8