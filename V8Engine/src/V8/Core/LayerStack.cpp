#include "v8pch.h"

#include "LayerStack.h"

namespace V8
{
LayerStack::LayerStack() { m_LayerInsert = m_Layers.begin(); }

// Currently Layers in LayerStack are deleted only Application is shutdowned
LayerStack::~LayerStack()
{
    for (Layer* layer : m_Layers)
    {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer)
{
    m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
}

void LayerStack::PushOverlay(Layer* overlay) { m_Layers.emplace_back(overlay); }

// Here Only pop layer from LayerStack, not delete
void LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
        m_LayerInsert--;
    }
}

// Here Only pop layer from LayerStack, not delete
void LayerStack::PopOverlay(Layer* overlay)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
}

} // namespace V8
