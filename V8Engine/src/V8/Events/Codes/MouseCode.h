#pragma once

#include <BulletFarm.h>

#include "CommonCodeCore.h"

namespace V8
{
namespace Mouse
{
using MouseCode = uint16;

// !TODO: support (glfw, win32api)
enum : MouseCode
{
    // From glfw3.h
    Button0 = 0,
    Button1 = 1,
    Button2 = 2,
    Button3 = 3,
    Button4 = 4,
    Button5 = 5,
    Button6 = 6,
    Button7 = 7,

    ButtonLast = Button7,
    ButtonLeft = Button0,
    ButtonRight = Button1,
    ButtonMiddle = Button2
};

} // namespace Mouse

struct MouseCodeMapper
{
private:
    MouseCodeMapper(const MouseCodeMapper&) = delete;
    MouseCodeMapper& operator=(const MouseCodeMapper&) = delete;

public:
    MouseCodeMapper(uint16_t mode);

    Mouse::MouseCode ToMouseCodeImpl(int32_t platformCode);
    int32_t ToPlatformCodeImpl(Mouse::MouseCode mouseCode);

    inline std::string ToString() const { return m_ModeName; }

private:
    void InitMap(uint16 keyMode);

private:
    using PlatformToMouseMap = std::unordered_map<int32_t, Mouse::MouseCode>;
    using MouseToPlatformMap = std::unordered_map<Mouse::MouseCode, int32_t>;

    PlatformToMouseMap m_PtoM;
    MouseToPlatformMap m_MtoP;

    std::string m_ModeName;
};

class V8API MouseCodeUtil
{
private:
    MouseCodeUtil();

public:
    static MouseCodeUtil& Get();

    Mouse::MouseCode ToMouseCode(int32_t platformCode);
    int32_t ToPlatformCode(Mouse::MouseCode mouseCode);

    inline std::string ToString() const { return m_Mapper.ToString(); }

private:
    MouseCodeMapper m_Mapper;
};

} // namespace V8