#pragma once

#include "V8/Events/Codes/KeyCode.h"
#include "V8/Events/Event.h"

namespace V8
{
using namespace Key;

class KeyEvent : public Event
{
    GENERATE_TYPE_INFO(KeyEvent)
protected:
    KeyEvent(const int32& platformCode)
    {
        m_KeyCode = KeyCodeUtil::Get().ToKeyCode(platformCode);
    }

public:
    KeyCode GetKeyCode() const { return m_KeyCode; }
    int32 GetPlatformCode() const
    {
        return KeyCodeUtil::Get().ToPlatformCode(m_KeyCode);
    }

    EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)

protected:
    KeyCode m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
    GENERATE_TYPE_INFO(KeyPressedEvent)
public:
    KeyPressedEvent(const int32& platformCode, bool isRepeat = false)
        : KeyEvent(platformCode), m_IsRepeat(isRepeat)
    {
    }

    bool IsRepeat() const { return m_IsRepeat; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat
           << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    bool m_IsRepeat;
};

class KeyReleasedEvent : public KeyEvent
{
    GENERATE_TYPE_INFO(KeyReleasedEvent)
public:
    KeyReleasedEvent(const int32& platformCode) : KeyEvent(platformCode) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
    GENERATE_TYPE_INFO(KeyTypedEvent)
public:
    KeyTypedEvent(const int32& platformCode) : KeyEvent(platformCode) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};
} // namespace V8