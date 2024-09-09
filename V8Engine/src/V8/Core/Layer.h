#pragma once

#include "V8/Core/Core.h"
#include "V8/Events/Event.h"

namespace V8
{
class V8API Layer
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach(); // add to Layer Stack
    virtual void OnDetach(); // remove from Layer Stack
    virtual void OnUpdate();
    virtual void OnGUIRender();
    virtual void OnEvent(Event& event);

    inline const std::string& GetName() const { return m_DebugName; }

private:
    std::string m_DebugName;
};

} // namespace V8
