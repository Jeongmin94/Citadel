#include "v8pch.h"

#include "KeyCode.h"

namespace V8
{

KeyCodeUtil* KeyCodeUtil::s_Instance = nullptr;

void KeyCodeUtil::Init()
{
    CORE_ASSERT(!s_Instance, "KeyCodeUtil already exists!");
    s_Instance = 
}

} // namespace V8