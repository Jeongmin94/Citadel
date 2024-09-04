#pragma once

#include "V8/Events/Event.h"

namespace V8
{
class WindowResizedEvent : public Event
{
    GENERATE_TYPE_INFO(WindowResizedEvent)
public:
    WindowResizedEvent(uint16 width, uint16 height)
        : m_Width(width), m_Height(height)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizedEvent:" << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EC_Application | EC_Keyboard)

    const uint16 GetWidth() const { return m_Width; }
    const uint16 GetHeight() const { return m_Height; }

private:
    uint16 m_Width, m_Height;
};

class WindowClosedEvent : public Event
{
    GENERATE_TYPE_INFO(WindowClosedEvent)
public:
    WindowClosedEvent(){};

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EC_Application)
};
} // namespace V8