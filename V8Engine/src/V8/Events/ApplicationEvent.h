#pragma once

#include "V8/Events/Event.h"

namespace V8
{
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(uint32 width, uint32 height)
        : _width(width), _height(height)
    {
    }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategory::Application |
                         EventCategory::Keyboard);

private:
    uint32 _width, _height;
};
} // namespace V8