#include "v8pch.h"

#include "MacInclude.h"

namespace V8
{

IWindow* IWindow::Create(const WindowProps& props)
{
    return new MacWindow(props);
}

}
