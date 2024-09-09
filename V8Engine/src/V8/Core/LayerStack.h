#pragma once

#include "V8/Core/Core.h"

#include <vector>

namespace V8
{
class Layer;

class V8API LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

private:
    std::vector<Layer*> m_Layers;
    uint32 m_LayerInsertIndex = 0;
};

} // namespace V8
