#pragma once

#include "v8pch.h"

#include "V8/Core/Core.h"

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
    None                       = 0,
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
    GENERATE_TYPE_INFO(Event)

public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual uint8 GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

public:
    bool IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & static_cast<uint8>(category);
    }

    inline bool IsHandled() const { return m_isHandled; }
    inline void SetIsHandled(bool handled) { m_isHandled |= handled; }

private:
    bool m_isHandled = false;
};

using EventCallbackBoolFn = std::function<bool(Event&)>;
using EventCallbackVoidFn = std::function<void(Event&)>;

class EventDispatcher
{
public:
    EventDispatcher(Event& event) : m_Event(event) {}

    template <typename T, typename F>
    bool Dispatch(const F& func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.SetIsHandled(func(static_cast<T&>(m_Event)));
            return true;
        }

        return false;
    }

private:
    Event& m_Event;
};

class EventHandlerRegistry
{
public:
    template <typename EventType>
    void RegisterHandler(const std::function<bool(EventType&)>& handler)
    {
        TypeHash key = EventType::StaticType().GetTypeHash();

        if (m_HandlerMap.find(key) != m_HandlerMap.end())
        {
            CORE_WARN("This handler is already registered: {0}",
                      EventType::StaticType().ToString());

            return;
        }

        m_HandlerMap[key] = [handler](Event& e)
        { return handler(static_cast<EventType&>(e)); };
    }

    bool HandleEvent(Event& e) const;

private:
    using EventHandlerMap = std::unordered_map<TypeHash, EventCallbackBoolFn>;
    EventHandlerMap m_HandlerMap;
};

} // namespace V8