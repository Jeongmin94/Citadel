#include "v8pch.h"

#include "ImGuiLayer.h"

namespace V8
{
ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
ImGuiLayer::~ImGuiLayer() {}
void ImGuiLayer::OnAttach() {}
void ImGuiLayer::OnDetach() {}
void ImGuiLayer::OnUpdate() {}
void ImGuiLayer::OnEvent(Event& event) {}
} // namespace V8