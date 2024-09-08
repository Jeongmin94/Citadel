#pragma once

#ifdef Win32API
// TODO: add Win32 header
constexpr uint16_t KEY_MODE = 0;
#else
constexpr uint16_t KEY_MODE = 1;
#endif

namespace V8
{

namespace KeyMode
{
enum : uint16_t
{
    WIN32API = 0,
    GLFW = 1,
};
}

} // namespace V8