#include "v8pch.h"

#include "LayerStack.h"
#include "V8/Core/Layer.h"

namespace V8
{
LayerStack::LayerStack() { CORE_INFO("Initializing LayerStack"); }

// Currently Layers in LayerStack are deleted only Application is shutdowned
LayerStack::~LayerStack()
{
    for (Layer* layer : m_Layers)
    {
        if (layer)
        {
            layer->OnDetach();
            delete layer;
        }
        else
        {
            CORE_ERROR("layer is invalid");
        }
    }
}

void LayerStack::PushLayer(Layer* layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
}

void LayerStack::PushOverlay(Layer* overlay) { m_Layers.emplace_back(overlay); }

// Here Only pop layer from LayerStack, not delete
void LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
        --m_LayerInsertIndex;
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

std::string LayerStack::ToString() const
{
    std::stringstream ss;
    ss << "\n[LayerStack Info]\n";
    for (auto layer : m_Layers)
    {
        ss << " - " << layer->GetName() << '\n';
    }

    return ss.str();
}

} // namespace V8
