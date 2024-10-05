#include "v8pch.h"

#include "MacInclude.h"

namespace V8
{

#ifdef V8_PLATFORM_MAC
IWindow* IWindow::Create(const WindowProps& props)
{
    return new MacWindow(props);
}
#endif // V8_PLATFORM_MAC

} // namespace V8
