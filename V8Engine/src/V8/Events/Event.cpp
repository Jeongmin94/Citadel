#include "v8pch.h"

#include "Event.h"

namespace V8
{

std::ostream& operator<<(std::ostream& out, const Event& e)
{
    return out << e.ToString();
}

bool EventHandlerRegistry::HandleEvent(Event& e) const
{
    const Type& eventType = e.GetType();
    auto it = m_HandlerMap.find(eventType.GetTypeHash());
    if (it == m_HandlerMap.end())
    {
        CORE_WARN("This event's handler is not found: {0}",
                  eventType.ToString());

        return false;
    }

    return it->second(e);
}

} // namespace V8