#pragma once

#include "V8/Core.h"
#include "v8pch.h"

namespace V8
{
// Ref: https://github.com/TheCherno/Hazel/tree/master/Hazel/src/Hazel/Events
// Events in V8Engine are currently blocking

// clang-format off
enum class EventType
{
    None = 0,

    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,

    AppTick, AppUpdate, AppRender,

    KeyPressed, KeyReleased, KeyTyped,

    MouseMoved, MouseScrolled,

    MouseButtonPressed, MouseButtonReleased,
};

enum EventCategory
{
    None                    = 0,
    EC_Application             = BIT(0),
    EC_Input                   = BIT(1),
    EC_Keyboard                = BIT(2),
    EC_Mouse                   = BIT(3),
    EC_MouseButton             = BIT(4),
};

#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::##type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; /* "type" */ }

#define EVENT_CLASS_CATEGORY(category) \
    virtual uint8 GetCategoryFlags() const override { return static_cast<uint8>(category); }

// clang-format on

class Event
{
public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual uint8 GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

public:
    bool m_isHandled = false;

    bool IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & static_cast<uint8>(category);
    }
};

class EventDispatcher
{
public:
    EventDispatcher(Event& event) : m_Event(event) {}

    template <typename T>
    using EventFn = std::function<bool>(T&);

    template <typename T>
    bool Dispatch(EventFn<T> func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.m_isHandled = func(static_cast<T&>(m_Event));
            return true;
        }

        return false;
    }

private:
    Event& m_Event;
};

std::ostream& operator<<(std::ostream& out, const Event& e)
{
    out << e.ToString();
    return out;
}

} // namespace V8