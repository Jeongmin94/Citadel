#pragma once

#include "V8/Events/Event.h"

namespace V8
{
class V8API WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(uint16 width, uint16 height)
        : m_Width(width), m_Height(height)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent:" << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EC_Application | EC_Keyboard);

private:
    uint16 m_Width, m_Height;
};

class V8API WindowCloseEvent : public Event
{
public:
    WindowCloseEvent(){};

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(EC_Application);
};
} // namespace V8