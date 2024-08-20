#pragma once

#include "V8/Core.h"

#include <functional>
#include <string>

namespace V8
{
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

enum class EventCategory
{
    None                    = 0,
    Application             = BIT(0),
    Input                   = BIT(1),
    Keyboard                = BIT(2),
    Mouse                   = BIT(3),
    MouseButton             = BIT(4),
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; /* "type" */ }

#define EVENT_CLASS_CATEGORY(category) virtual uint32 GetCategoryFlags() const override { return static_cast<uint32>(category); }

// clang-format on

class Event
{
public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

public:
    bool Handled = false;

    bool IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & static_cast<uint32>(category);
    }
};

} // namespace V8