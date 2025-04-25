#include "v8pch.h"

#include "WindowsInclude.h"

namespace V8
{

#ifdef V8_PLATFORM_WINDOWS
IWindow* IWindow::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}
#endif

} // namespace V8
