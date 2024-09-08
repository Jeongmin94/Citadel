#pragma once

#include "V8/Events/Codes/MouseCode.h"
#include "V8/Events/Event.h"

namespace V8
{
using namespace Mouse;

class MouseMovedEvent : public Event
{
    GENERATE_TYPE_INFO(MouseMovedEvent)
public:
    MouseMovedEvent(const float32& x, const float32& y)
        : m_MouseX(x), m_MouseY(y){};

    float32 GetX() const { return m_MouseX; }
    float32 GetY() const { return m_MouseY; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)

private:
    float32 m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
    GENERATE_TYPE_INFO(MouseScrolledEvent)
public:
    MouseScrolledEvent(const float32& offsetX, const float32& offsetY)
        : m_OffsetX(offsetX), m_OffsetY(offsetY){};

    float32 GetOffsetX() const { return m_OffsetX; }
    float32 GetOffsetY() const { return m_OffsetY; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)

private:
    float32 m_OffsetX, m_OffsetY;
};

class MouseButtonEvent : public Event
{
    GENERATE_TYPE_INFO(MouseButtonEvent)
public:
    MouseCode GetMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input | EC_MouseButton)

protected:
    MouseButtonEvent(const int32 platformButton) : m_Button(platformButton) {}

    MouseCode m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
    GENERATE_TYPE_INFO(MouseButtonPressedEvent)
public:
    MouseButtonPressedEvent(const int32 platformButton)
        : MouseButtonEvent(platformButton)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
    GENERATE_TYPE_INFO(MouseButtonReleasedEvent)
public:
    MouseButtonReleasedEvent(const int32 platformButton)
        : MouseButtonEvent(platformButton)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

} // namespace V8