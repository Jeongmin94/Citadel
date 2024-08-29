#pragma once

#include "V8/Core/Layer.h"

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
    void OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);

private:
    float m_Time = 0.0f;
};
} // namespace V8