#pragma once

#include "V8/Core/Layer.h"

namespace V8
{
class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnEvent(Event& event) override;

private:
};
} // namespace V8