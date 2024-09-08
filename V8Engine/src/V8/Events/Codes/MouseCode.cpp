#include "v8pch.h"

#include "CommonCodeCore.h"
#include "MouseCode.h"

#ifdef Win32API
// TODO: add Win32 header
#else
#include <GLFW/glfw3.h>
#endif

namespace V8
{

MouseCodeMapper::MouseCodeMapper(uint16_t mode) {}

Mouse::MouseCode MouseCodeMapper::ToMouseCode(int32_t platformCode)
{
    return m_PtoM[platformCode];
}

int32_t MouseCodeMapper::ToPlatformCode(Mouse::MouseCode mouseCode)
{
    return m_MtoP[mouseCode];
}

void MouseCodeMapper::InitMap(uint16 keyMode)
{
    switch (keyMode)
    {
        case KeyMode::GLFW:
        {
            m_ModeName = std::string("MouseModeGLFW");
            m_PtoM[GLFW_MOUSE_BUTTON_1] = Mouse::Button0;
            m_PtoM[GLFW_MOUSE_BUTTON_2] = Mouse::Button1;
            m_PtoM[GLFW_MOUSE_BUTTON_3] = Mouse::Button2;
            m_PtoM[GLFW_MOUSE_BUTTON_4] = Mouse::Button3;
            m_PtoM[GLFW_MOUSE_BUTTON_5] = Mouse::Button4;
            m_PtoM[GLFW_MOUSE_BUTTON_6] = Mouse::Button5;
            m_PtoM[GLFW_MOUSE_BUTTON_7] = Mouse::Button6;
            m_PtoM[GLFW_MOUSE_BUTTON_8] = Mouse::Button7;

            for (const auto& pair : m_PtoM)
            {
                m_MtoP[pair.second] = pair.first;
            }
            break;
        }

        case KeyMode::WIN32API:
        {
            m_ModeName = std::string("MouseModeWIN32API");
            break;
        }
    }
}

MouseCodeUtil::MouseCodeUtil() : m_Mapper(CommonCode::KEY_MODE) {}

MouseCodeUtil& MouseCodeUtil::Get()
{
    static MouseCodeUtil s_MouseCodeUtil;
    return s_MouseCodeUtil;
}

Mouse::MouseCode MouseCodeUtil::ToMouseCode(int32_t platformCode)
{
    return m_Mapper.ToMouseCode(platformCode);
}

int32_t MouseCodeUtil::ToPlatformCode(Mouse::MouseCode mouseCode)
{
    return m_Mapper.ToPlatformCode(mouseCode);
}

} // namespace V8