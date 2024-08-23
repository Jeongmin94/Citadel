#pragma once

#include "V8/Events/Event.h"

namespace V8
{
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(uint16 width, uint16 height)
        : _width(width), _height(height)
    {
    }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EC_Application | EC_Keyboard);

private:
    uint16 _width, _height;
};
} // namespace V8