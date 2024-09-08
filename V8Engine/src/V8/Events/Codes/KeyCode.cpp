#include "v8pch.h"

#include "CommonCodeCore.h"
#include "KeyCode.h"

#ifdef Win32API
// TODO: add Win32 header
#else
#include <GLFW/glfw3.h>
#endif

namespace V8
{

KeyCodeUtil* KeyCodeUtil::s_KeyCodeUtil = nullptr;

KeyCodeUtil::KeyCodeUtil() : m_Mapper(KEY_MODE)
{
    CORE_ASSERT(!KeyCodeUtil::s_KeyCodeUtil, "{0}",
                "KeyCodeUtil already Exist!")

    KeyCodeUtil::s_KeyCodeUtil = this;

    CORE_ASSERT(KeyCodeUtil::s_KeyCodeUtil, "{0}",
                "KeyCodeUtil Intializing Failed!");
}

KeyCodeUtil& KeyCodeUtil::Get() { return *s_KeyCodeUtil; }

Key::KeyCode KeyCodeUtil::ToKeyCode(int32 platformCode)
{
    return s_KeyCodeUtil->m_Mapper.ToKeyCodeImpl(platformCode);
}

int32 KeyCodeUtil::ToPlatformCode(Key::KeyCode keyCode)
{
    return s_KeyCodeUtil->m_Mapper.ToPlatformCodeImpl(keyCode);
}

KeyCodeMapper::KeyCodeMapper(uint16 keyMode)
{
    switch (keyMode)
    {
        case KeyMode::GLFW:
        {
            m_ModeName = std::string("KeyModeGLFW");
            break;
        }
        case KeyMode::WIN32API:
        {
            m_ModeName = std::string("KeyModeWIN32API");
            break;
        }
    }

    InitMap(keyMode);
}

void KeyCodeMapper::InitMap(uint16 keyMode)
{
    switch (keyMode)
    {
        case KeyMode::GLFW:
        {
            // Initialize GLFW key code mappings
            m_PtoK[GLFW_KEY_SPACE] = Key::Space;
            m_PtoK[GLFW_KEY_APOSTROPHE] = Key::Apostrophe;
            m_PtoK[GLFW_KEY_COMMA] = Key::Comma;
            m_PtoK[GLFW_KEY_MINUS] = Key::Minus;
            m_PtoK[GLFW_KEY_PERIOD] = Key::Period;
            m_PtoK[GLFW_KEY_SLASH] = Key::Slash;
            m_PtoK[GLFW_KEY_0] = Key::D0;
            m_PtoK[GLFW_KEY_1] = Key::D1;
            m_PtoK[GLFW_KEY_2] = Key::D2;
            m_PtoK[GLFW_KEY_3] = Key::D3;
            m_PtoK[GLFW_KEY_4] = Key::D4;
            m_PtoK[GLFW_KEY_5] = Key::D5;
            m_PtoK[GLFW_KEY_6] = Key::D6;
            m_PtoK[GLFW_KEY_7] = Key::D7;
            m_PtoK[GLFW_KEY_8] = Key::D8;
            m_PtoK[GLFW_KEY_9] = Key::D9;
            m_PtoK[GLFW_KEY_SEMICOLON] = Key::Semicolon;
            m_PtoK[GLFW_KEY_EQUAL] = Key::Equal;
            m_PtoK[GLFW_KEY_A] = Key::A;
            m_PtoK[GLFW_KEY_B] = Key::B;
            m_PtoK[GLFW_KEY_C] = Key::C;
            m_PtoK[GLFW_KEY_D] = Key::D;
            m_PtoK[GLFW_KEY_E] = Key::E;
            m_PtoK[GLFW_KEY_F] = Key::F;
            m_PtoK[GLFW_KEY_G] = Key::G;
            m_PtoK[GLFW_KEY_H] = Key::H;
            m_PtoK[GLFW_KEY_I] = Key::I;
            m_PtoK[GLFW_KEY_J] = Key::J;
            m_PtoK[GLFW_KEY_K] = Key::K;
            m_PtoK[GLFW_KEY_L] = Key::L;
            m_PtoK[GLFW_KEY_M] = Key::M;
            m_PtoK[GLFW_KEY_N] = Key::N;
            m_PtoK[GLFW_KEY_O] = Key::O;
            m_PtoK[GLFW_KEY_P] = Key::P;
            m_PtoK[GLFW_KEY_Q] = Key::Q;
            m_PtoK[GLFW_KEY_R] = Key::R;
            m_PtoK[GLFW_KEY_S] = Key::S;
            m_PtoK[GLFW_KEY_T] = Key::T;
            m_PtoK[GLFW_KEY_U] = Key::U;
            m_PtoK[GLFW_KEY_V] = Key::V;
            m_PtoK[GLFW_KEY_W] = Key::W;
            m_PtoK[GLFW_KEY_X] = Key::X;
            m_PtoK[GLFW_KEY_Y] = Key::Y;
            m_PtoK[GLFW_KEY_Z] = Key::Z;
            m_PtoK[GLFW_KEY_LEFT_BRACKET] = Key::LeftBracket;
            m_PtoK[GLFW_KEY_BACKSLASH] = Key::Backslash;
            m_PtoK[GLFW_KEY_RIGHT_BRACKET] = Key::RightBracket;
            m_PtoK[GLFW_KEY_GRAVE_ACCENT] = Key::GraveAccent;
            m_PtoK[GLFW_KEY_WORLD_1] = Key::World1;
            m_PtoK[GLFW_KEY_WORLD_2] = Key::World2;
            m_PtoK[GLFW_KEY_ESCAPE] = Key::Escape;
            m_PtoK[GLFW_KEY_ENTER] = Key::Enter;
            m_PtoK[GLFW_KEY_TAB] = Key::Tab;
            m_PtoK[GLFW_KEY_BACKSPACE] = Key::Backspace;
            m_PtoK[GLFW_KEY_INSERT] = Key::Insert;
            m_PtoK[GLFW_KEY_DELETE] = Key::Delete;
            m_PtoK[GLFW_KEY_RIGHT] = Key::Right;
            m_PtoK[GLFW_KEY_LEFT] = Key::Left;
            m_PtoK[GLFW_KEY_DOWN] = Key::Down;
            m_PtoK[GLFW_KEY_UP] = Key::Up;
            m_PtoK[GLFW_KEY_PAGE_UP] = Key::PageUp;
            m_PtoK[GLFW_KEY_PAGE_DOWN] = Key::PageDown;
            m_PtoK[GLFW_KEY_HOME] = Key::Home;
            m_PtoK[GLFW_KEY_END] = Key::End;
            m_PtoK[GLFW_KEY_CAPS_LOCK] = Key::CapsLock;
            m_PtoK[GLFW_KEY_SCROLL_LOCK] = Key::ScrollLock;
            m_PtoK[GLFW_KEY_NUM_LOCK] = Key::NumLock;
            m_PtoK[GLFW_KEY_PRINT_SCREEN] = Key::PrintScreen;
            m_PtoK[GLFW_KEY_PAUSE] = Key::Pause;
            m_PtoK[GLFW_KEY_F1] = Key::F1;
            m_PtoK[GLFW_KEY_F2] = Key::F2;
            m_PtoK[GLFW_KEY_F3] = Key::F3;
            m_PtoK[GLFW_KEY_F4] = Key::F4;
            m_PtoK[GLFW_KEY_F5] = Key::F5;
            m_PtoK[GLFW_KEY_F6] = Key::F6;
            m_PtoK[GLFW_KEY_F7] = Key::F7;
            m_PtoK[GLFW_KEY_F8] = Key::F8;
            m_PtoK[GLFW_KEY_F9] = Key::F9;
            m_PtoK[GLFW_KEY_F10] = Key::F10;
            m_PtoK[GLFW_KEY_F11] = Key::F11;
            m_PtoK[GLFW_KEY_F12] = Key::F12;
            m_PtoK[GLFW_KEY_F13] = Key::F13;
            m_PtoK[GLFW_KEY_F14] = Key::F14;
            m_PtoK[GLFW_KEY_F15] = Key::F15;
            m_PtoK[GLFW_KEY_F16] = Key::F16;
            m_PtoK[GLFW_KEY_F17] = Key::F17;
            m_PtoK[GLFW_KEY_F18] = Key::F18;
            m_PtoK[GLFW_KEY_F19] = Key::F19;
            m_PtoK[GLFW_KEY_F20] = Key::F20;
            m_PtoK[GLFW_KEY_F21] = Key::F21;
            m_PtoK[GLFW_KEY_F22] = Key::F22;
            m_PtoK[GLFW_KEY_F23] = Key::F23;
            m_PtoK[GLFW_KEY_F24] = Key::F24;
            m_PtoK[GLFW_KEY_F25] = Key::F25;
            m_PtoK[GLFW_KEY_KP_0] = Key::KP0;
            m_PtoK[GLFW_KEY_KP_1] = Key::KP1;
            m_PtoK[GLFW_KEY_KP_2] = Key::KP2;
            m_PtoK[GLFW_KEY_KP_3] = Key::KP3;
            m_PtoK[GLFW_KEY_KP_4] = Key::KP4;
            m_PtoK[GLFW_KEY_KP_5] = Key::KP5;
            m_PtoK[GLFW_KEY_KP_6] = Key::KP6;
            m_PtoK[GLFW_KEY_KP_7] = Key::KP7;
            m_PtoK[GLFW_KEY_KP_8] = Key::KP8;
            m_PtoK[GLFW_KEY_KP_9] = Key::KP9;
            m_PtoK[GLFW_KEY_KP_DECIMAL] = Key::KPDecimal;
            m_PtoK[GLFW_KEY_KP_DIVIDE] = Key::KPDivide;
            m_PtoK[GLFW_KEY_KP_MULTIPLY] = Key::KPMultiply;
            m_PtoK[GLFW_KEY_KP_SUBTRACT] = Key::KPSubtract;
            m_PtoK[GLFW_KEY_KP_ADD] = Key::KPAdd;
            m_PtoK[GLFW_KEY_KP_ENTER] = Key::KPEnter;
            m_PtoK[GLFW_KEY_KP_EQUAL] = Key::KPEqual;
            m_PtoK[GLFW_KEY_LEFT_SHIFT] = Key::LeftShift;
            m_PtoK[GLFW_KEY_LEFT_CONTROL] = Key::LeftControl;
            m_PtoK[GLFW_KEY_LEFT_ALT] = Key::LeftAlt;
            m_PtoK[GLFW_KEY_LEFT_SUPER] = Key::LeftSuper;
            m_PtoK[GLFW_KEY_RIGHT_SHIFT] = Key::RightShift;
            m_PtoK[GLFW_KEY_RIGHT_CONTROL] = Key::RightControl;
            m_PtoK[GLFW_KEY_RIGHT_ALT] = Key::RightAlt;
            m_PtoK[GLFW_KEY_RIGHT_SUPER] = Key::RightSuper;
            m_PtoK[GLFW_KEY_MENU] = Key::Menu;

            // Initialize reverse mapping
            for (const auto& pair : m_PtoK)
            {
                m_KtoP[pair.second] = pair.first;
            }
            break;
        }
        case KeyMode::WIN32API:
        {
            break;
        }
    }
}

Key::KeyCode KeyCodeMapper::ToKeyCodeImpl(int32 platformCode)
{
    return m_PtoK[platformCode];
}

int32 KeyCodeMapper::ToPlatformCodeImpl(Key::KeyCode keyCode)
{
    return m_KtoP[keyCode];
}

} // namespace V8