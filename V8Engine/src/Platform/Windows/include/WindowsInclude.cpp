#include "v8pch.h"

#include "WindowsInclude.h"

namespace V8
{

IWindow* IWindow::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

}
