#pragma once

#include "V8/Core.h"

#include <functional>
#include <string>

namespace V8
{
// Events in V8Engine are currently blocking

enum class EventType
{
    None = 0,

    // window events
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,

    // application events
    AppTick,
    AppUpdate,
    AppRender,

    // keyboard events
    KeyPressed,
    KeyReleased,
    KeyTyped,

    // mouse events
    MouseMoved,
    MouseScrolled,

    // mouse button events
    MouseButtonPressed,
    MouseButtonReleased,
};

enum EventCategory
{
    None = 0,
    EC_Application = BIT(0),
    EC_Input = BIT(1),
    EC_Keyboard = BIT(2),
    EC_Mouse = BIT(3),
    EC_MouseButton = BIT(4)
};

class Event
{
public:
    virtual ~Event() = default;
};

} // namespace V8