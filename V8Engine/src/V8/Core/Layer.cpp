#include "v8pch.h"

#include "Layer.h"

namespace V8
{
Layer::Layer(const std::string& name) : m_DebugName(name) {}

Layer::~Layer() {}

void Layer::OnAttach() {}

void Layer::OnDetach() {}

void Layer::OnUpdate() {}

void Layer::OnGUIRender() {}

void Layer::OnEvent(Event& event) {}

} // namespace V8
