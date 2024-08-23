#include "v8pch.h"

#include "Event.h"

namespace V8
{

std::ostream& operator<<(std::ostream& out, const Event& e)
{
    return out << e.ToString();
}

} // namespace V8