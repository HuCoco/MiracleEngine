#include "KeyBoardManager.h"
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>


Miracle::KeyBoardManager::KeyBoardManager()
{
	for (_I32 i = 0; i < NUM_FUNCITON_KEY; i++)
	{
		m_FunctionKeyStates[i] = FunctionKeyState::Up;
	}
}


Miracle::KeyBoardManager::~KeyBoardManager()
{
}

void Miracle::KeyBoardManager::SetFunctionKeyState(FunctionKey a_Key, FunctionKeyState a_State)
{
	m_FunctionKeyStates[a_Key] = a_State;
}


bool Miracle::KeyBoardManager::IsFunctionKeyUp(FunctionKey a_Key) const
{
	return m_FunctionKeyStates[a_Key] == FunctionKeyState::Up;
}

bool Miracle::KeyBoardManager::IsFunctionKeyDown(FunctionKey a_Key) const
{
	return m_FunctionKeyStates[a_Key] == FunctionKeyState::Down;
}

Miracle::KeyBoardManager::FunctionKey Miracle::KeyBoardManager::GetFunctionKeyFromMS(_U32 a_Input)
{
	switch (a_Input)
	{
	case VK_SPACE:				return FunctionKey::KEY_SPACE;
	case VK_OEM_7:				return FunctionKey::KEY_APOSTROPHE;
	case VK_OEM_COMMA:			return FunctionKey::KEY_COMMA;
	case VK_OEM_MINUS:			return FunctionKey::KEY_MINUS;
	case VK_OEM_PERIOD:			return FunctionKey::KEY_PERIOD;
	case VK_OEM_2:				return FunctionKey::KEY_SLASH;
	case '0':					return FunctionKey::KEY_0;
	case '1':					return FunctionKey::KEY_1;
	case '2':					return FunctionKey::KEY_2;
	case '3':					return FunctionKey::KEY_3;
	case '4':					return FunctionKey::KEY_4;
	case '5':					return FunctionKey::KEY_5;
	case '6':					return FunctionKey::KEY_6;
	case '7':					return FunctionKey::KEY_7;
	case '8':					return FunctionKey::KEY_8;
	case '9':					return FunctionKey::KEY_9;
	case VK_OEM_1:				return FunctionKey::KEY_SEMICOLON;
	case VK_OEM_PLUS:			return FunctionKey::KEY_EQUAL;
	case 'A':					return FunctionKey::KEY_A;
	case 'B':					return FunctionKey::KEY_B;
	case 'C':					return FunctionKey::KEY_C;
	case 'D':					return FunctionKey::KEY_D;
	case 'E':					return FunctionKey::KEY_E;
	case 'F':					return FunctionKey::KEY_F;
	case 'G':					return FunctionKey::KEY_G;
	case 'H':					return FunctionKey::KEY_H;
	case 'I':					return FunctionKey::KEY_I;
	case 'J':					return FunctionKey::KEY_J;
	case 'K':					return FunctionKey::KEY_K;
	case 'L':					return FunctionKey::KEY_L;
	case 'M':					return FunctionKey::KEY_M;
	case 'N':					return FunctionKey::KEY_N;
	case 'O':					return FunctionKey::KEY_O;
	case 'P':					return FunctionKey::KEY_P;
	case 'Q':					return FunctionKey::KEY_Q;
	case 'R':					return FunctionKey::KEY_R;
	case 'S':					return FunctionKey::KEY_S;
	case 'T':					return FunctionKey::KEY_T;
	case 'U':					return FunctionKey::KEY_U;
	case 'V':					return FunctionKey::KEY_V;
	case 'W':					return FunctionKey::KEY_W;
	case 'X':					return FunctionKey::KEY_X;
	case 'Y':					return FunctionKey::KEY_Y;
	case 'Z':					return FunctionKey::KEY_Z;
	case VK_OEM_4:				return FunctionKey::KEY_LEFT_BRACKET;
	case VK_OEM_5:				return FunctionKey::KEY_BACKSLASH;
	case VK_OEM_6:				return FunctionKey::KEY_RIGHT_BRACKET;
	case VK_OEM_3:				return FunctionKey::KEY_GRAVE_ACCENT;
	case VK_ESCAPE:				return FunctionKey::KEY_ESCAPE;
	case VK_RETURN:				return FunctionKey::KEY_ENTER;
	case VK_TAB:				return FunctionKey::KEY_TAB;
	case VK_BACK:				return FunctionKey::KEY_BACKSPACE;
	case VK_INSERT:				return FunctionKey::KEY_INSERT;
	case VK_DELETE:				return FunctionKey::KEY_DELETE;
	case VK_RIGHT:				return FunctionKey::KEY_RIGHT;
	case VK_LEFT:				return FunctionKey::KEY_LEFT;
	case VK_DOWN:				return FunctionKey::KEY_DOWN;
	case VK_UP:					return FunctionKey::KEY_UP;
	case VK_PRIOR:				return FunctionKey::KEY_PAGE_UP;
	case VK_NEXT:				return FunctionKey::KEY_PAGE_DOWN;
	case VK_HOME:				return FunctionKey::KEY_HOME;
	case VK_END:				return FunctionKey::KEY_END;
	case VK_CAPITAL:			return FunctionKey::KEY_CAPS_LOCK;
	case VK_SCROLL:				return FunctionKey::KEY_SCROLL_LOCK;
	case VK_NUMLOCK:			return FunctionKey::KEY_NUM_LOCK;
	case VK_SNAPSHOT:			return FunctionKey::KEY_PRINT_SCREEN;
	case VK_PAUSE:				return FunctionKey::KEY_PAUSE;
	case VK_F1:					return FunctionKey::KEY_F1;
	case VK_F2:					return FunctionKey::KEY_F2;
	case VK_F3:					return FunctionKey::KEY_F3;
	case VK_F4:					return FunctionKey::KEY_F4;
	case VK_F5:					return FunctionKey::KEY_F5;
	case VK_F6:					return FunctionKey::KEY_F6;
	case VK_F7:					return FunctionKey::KEY_F7;
	case VK_F8:					return FunctionKey::KEY_F8;
	case VK_F9:					return FunctionKey::KEY_F9;
	case VK_F10:				return FunctionKey::KEY_F10;
	case VK_F11:				return FunctionKey::KEY_F11;
	case VK_F12:				return FunctionKey::KEY_F12;
	case VK_F13:				return FunctionKey::KEY_F13;
	case VK_F14:				return FunctionKey::KEY_F14;
	case VK_F15:				return FunctionKey::KEY_F15;
	case VK_F16:				return FunctionKey::KEY_F16;
	case VK_F17:				return FunctionKey::KEY_F17;
	case VK_F18:				return FunctionKey::KEY_F18;
	case VK_F19:				return FunctionKey::KEY_F19;
	case VK_F20:				return FunctionKey::KEY_F20;
	case VK_F21:				return FunctionKey::KEY_F21;
	case VK_F22:				return FunctionKey::KEY_F22;
	case VK_F23:				return FunctionKey::KEY_F23;
	case VK_F24:				return FunctionKey::KEY_F24;
	case VK_NUMPAD0:			return FunctionKey::KEY_KP_0;
	case VK_NUMPAD1:			return FunctionKey::KEY_KP_1;
	case VK_NUMPAD2:			return FunctionKey::KEY_KP_2;
	case VK_NUMPAD3:			return FunctionKey::KEY_KP_3;
	case VK_NUMPAD4:			return FunctionKey::KEY_KP_4;
	case VK_NUMPAD5:			return FunctionKey::KEY_KP_5;
	case VK_NUMPAD6:			return FunctionKey::KEY_KP_6;
	case VK_NUMPAD7:			return FunctionKey::KEY_KP_7;
	case VK_NUMPAD8:			return FunctionKey::KEY_KP_8;
	case VK_NUMPAD9:			return FunctionKey::KEY_KP_9;
	case VK_DECIMAL:			return FunctionKey::KEY_KP_DECIMAL;
	case VK_DIVIDE:				return FunctionKey::KEY_KP_DIVIDE;
	case VK_MULTIPLY:			return FunctionKey::KEY_KP_MULTIPLY;
	case VK_SUBTRACT:			return FunctionKey::KEY_KP_SUBTRACT;
	case VK_ADD:				return FunctionKey::KEY_KP_ADD;
	case VK_SHIFT:
	{
		if (GetKeyState(VK_LSHIFT))
		{
			return FunctionKey::KEY_LEFT_SHIFT;
		}
		else if (GetKeyState(VK_RSHIFT))
		{
			return FunctionKey::KEY_RIGHT_SHIFT;
		}
	}
	break;

	case VK_CONTROL:
	{
		if (GetAsyncKeyState(VK_LCONTROL))
		{
			return FunctionKey::KEY_LEFT_CONTROL;
		}
		else if (GetAsyncKeyState(VK_RCONTROL))
		{
			return FunctionKey::KEY_RIGHT_CONTROL;
		}
		else
		{
			return FunctionKey::KEY_LEFT_CONTROL;
		}
	}
	case VK_MENU:
	{
		if (GetAsyncKeyState(VK_LMENU))
		{
			return FunctionKey::KEY_LEFT_ALT;
		}
		else if (GetAsyncKeyState(VK_RMENU))
		{
			return FunctionKey::KEY_RIGHT_ALT;
		}
	}
	break;
	default:							return FunctionKey::UNKOWN;
	}
	return FunctionKey::UNKOWN;
}

Miracle::KeyBoardManager::FunctionKey Miracle::KeyBoardManager::GetFunctionKeyFromGLFW(_U32 a_Input)
{
	switch (a_Input)
	{
	case GLFW_KEY_SPACE:				return FunctionKey::KEY_SPACE;
	case GLFW_KEY_APOSTROPHE:			return FunctionKey::KEY_APOSTROPHE;
	case GLFW_KEY_COMMA:				return FunctionKey::KEY_COMMA;
	case GLFW_KEY_MINUS:				return FunctionKey::KEY_MINUS;
	case GLFW_KEY_PERIOD:				return FunctionKey::KEY_PERIOD;
	case GLFW_KEY_SLASH:				return FunctionKey::KEY_SLASH;
	case GLFW_KEY_0:					return FunctionKey::KEY_0;
	case GLFW_KEY_1:					return FunctionKey::KEY_1;
	case GLFW_KEY_2:					return FunctionKey::KEY_2;
	case GLFW_KEY_3:					return FunctionKey::KEY_3;
	case GLFW_KEY_4:					return FunctionKey::KEY_4;
	case GLFW_KEY_5:					return FunctionKey::KEY_5;
	case GLFW_KEY_6:					return FunctionKey::KEY_6;
	case GLFW_KEY_7:					return FunctionKey::KEY_7;
	case GLFW_KEY_8:					return FunctionKey::KEY_8;
	case GLFW_KEY_9:					return FunctionKey::KEY_9;
	case GLFW_KEY_SEMICOLON:			return FunctionKey::KEY_SEMICOLON;
	case GLFW_KEY_EQUAL:				return FunctionKey::KEY_EQUAL;
	case GLFW_KEY_A:					return FunctionKey::KEY_A;
	case GLFW_KEY_B:					return FunctionKey::KEY_B;
	case GLFW_KEY_C:					return FunctionKey::KEY_C;
	case GLFW_KEY_D:					return FunctionKey::KEY_D;
	case GLFW_KEY_E:					return FunctionKey::KEY_E;
	case GLFW_KEY_F:					return FunctionKey::KEY_F;
	case GLFW_KEY_G:					return FunctionKey::KEY_G;
	case GLFW_KEY_H:					return FunctionKey::KEY_H;
	case GLFW_KEY_I:					return FunctionKey::KEY_I;
	case GLFW_KEY_J:					return FunctionKey::KEY_J;
	case GLFW_KEY_K:					return FunctionKey::KEY_K;
	case GLFW_KEY_L:					return FunctionKey::KEY_L;
	case GLFW_KEY_M:					return FunctionKey::KEY_M;
	case GLFW_KEY_N:					return FunctionKey::KEY_N;
	case GLFW_KEY_O:					return FunctionKey::KEY_O;
	case GLFW_KEY_P:					return FunctionKey::KEY_P;
	case GLFW_KEY_Q:					return FunctionKey::KEY_Q;
	case GLFW_KEY_R:					return FunctionKey::KEY_R;
	case GLFW_KEY_S:					return FunctionKey::KEY_S;
	case GLFW_KEY_T:					return FunctionKey::KEY_T;
	case GLFW_KEY_U:					return FunctionKey::KEY_U;
	case GLFW_KEY_V:					return FunctionKey::KEY_V;
	case GLFW_KEY_W:					return FunctionKey::KEY_W;
	case GLFW_KEY_X:					return FunctionKey::KEY_X;
	case GLFW_KEY_Y:					return FunctionKey::KEY_Y;
	case GLFW_KEY_Z:					return FunctionKey::KEY_Z;
	case GLFW_KEY_LEFT_BRACKET:			return FunctionKey::KEY_LEFT_BRACKET;
	case GLFW_KEY_BACKSLASH:			return FunctionKey::KEY_BACKSLASH;
	case GLFW_KEY_RIGHT_BRACKET:		return FunctionKey::KEY_RIGHT_BRACKET;
	case GLFW_KEY_GRAVE_ACCENT:			return FunctionKey::KEY_GRAVE_ACCENT;
	case GLFW_KEY_ESCAPE:				return FunctionKey::KEY_ESCAPE;
	case GLFW_KEY_ENTER:				return FunctionKey::KEY_ENTER;
	case GLFW_KEY_TAB:					return FunctionKey::KEY_TAB;
	case GLFW_KEY_BACKSPACE:			return FunctionKey::KEY_BACKSPACE;
	case GLFW_KEY_INSERT:				return FunctionKey::KEY_INSERT;
	case GLFW_KEY_DELETE:				return FunctionKey::KEY_DELETE;
	case GLFW_KEY_RIGHT:				return FunctionKey::KEY_RIGHT;
	case GLFW_KEY_LEFT:					return FunctionKey::KEY_LEFT;
	case GLFW_KEY_DOWN:					return FunctionKey::KEY_DOWN;
	case GLFW_KEY_UP:					return FunctionKey::KEY_UP;
	case GLFW_KEY_PAGE_UP:				return FunctionKey::KEY_PAGE_UP;
	case GLFW_KEY_PAGE_DOWN:			return FunctionKey::KEY_PAGE_DOWN;
	case GLFW_KEY_HOME:					return FunctionKey::KEY_HOME;
	case GLFW_KEY_END:					return FunctionKey::KEY_END;
	case GLFW_KEY_CAPS_LOCK:			return FunctionKey::KEY_CAPS_LOCK;
	case GLFW_KEY_SCROLL_LOCK:			return FunctionKey::KEY_SCROLL_LOCK;
	case GLFW_KEY_NUM_LOCK:				return FunctionKey::KEY_NUM_LOCK;
	case GLFW_KEY_PRINT_SCREEN:			return FunctionKey::KEY_PRINT_SCREEN;
	case GLFW_KEY_PAUSE:				return FunctionKey::KEY_PAUSE;
	case GLFW_KEY_F1:					return FunctionKey::KEY_F1;
	case GLFW_KEY_F2:					return FunctionKey::KEY_F2;
	case GLFW_KEY_F3:					return FunctionKey::KEY_F3;
	case GLFW_KEY_F4:					return FunctionKey::KEY_F4;
	case GLFW_KEY_F5:					return FunctionKey::KEY_F5;
	case GLFW_KEY_F6:					return FunctionKey::KEY_F6;
	case GLFW_KEY_F7:					return FunctionKey::KEY_F7;
	case GLFW_KEY_F8:					return FunctionKey::KEY_F8;
	case GLFW_KEY_F9:					return FunctionKey::KEY_F9;
	case GLFW_KEY_F10:					return FunctionKey::KEY_F10;
	case GLFW_KEY_F11:					return FunctionKey::KEY_F11;
	case GLFW_KEY_F12:					return FunctionKey::KEY_F12;
	case GLFW_KEY_F13:					return FunctionKey::KEY_F13;
	case GLFW_KEY_F14:					return FunctionKey::KEY_F14;
	case GLFW_KEY_F15:					return FunctionKey::KEY_F15;
	case GLFW_KEY_F16:					return FunctionKey::KEY_F16;
	case GLFW_KEY_F17:					return FunctionKey::KEY_F17;
	case GLFW_KEY_F18:					return FunctionKey::KEY_F18;
	case GLFW_KEY_F19:					return FunctionKey::KEY_F19;
	case GLFW_KEY_F20:					return FunctionKey::KEY_F20;
	case GLFW_KEY_F21:					return FunctionKey::KEY_F21;
	case GLFW_KEY_F22:					return FunctionKey::KEY_F22;
	case GLFW_KEY_F23:					return FunctionKey::KEY_F23;
	case GLFW_KEY_F24:					return FunctionKey::KEY_F24;
	case GLFW_KEY_F25:					return FunctionKey::KEY_F25;
	case GLFW_KEY_KP_0:					return FunctionKey::KEY_KP_0;
	case GLFW_KEY_KP_1:					return FunctionKey::KEY_KP_1;
	case GLFW_KEY_KP_2:					return FunctionKey::KEY_KP_2;
	case GLFW_KEY_KP_3:					return FunctionKey::KEY_KP_3;
	case GLFW_KEY_KP_4:					return FunctionKey::KEY_KP_4;
	case GLFW_KEY_KP_5:					return FunctionKey::KEY_KP_5;
	case GLFW_KEY_KP_6:					return FunctionKey::KEY_KP_6;
	case GLFW_KEY_KP_7:					return FunctionKey::KEY_KP_7;
	case GLFW_KEY_KP_8:					return FunctionKey::KEY_KP_8;
	case GLFW_KEY_KP_9:					return FunctionKey::KEY_KP_9;
	case GLFW_KEY_KP_DECIMAL:			return FunctionKey::KEY_KP_DECIMAL;
	case GLFW_KEY_KP_DIVIDE:			return FunctionKey::KEY_KP_DIVIDE;
	case GLFW_KEY_KP_MULTIPLY:			return FunctionKey::KEY_KP_MULTIPLY;
	case GLFW_KEY_KP_SUBTRACT:			return FunctionKey::KEY_KP_SUBTRACT;
	case GLFW_KEY_KP_ADD:				return FunctionKey::KEY_KP_ADD;
	case GLFW_KEY_KP_ENTER:				return FunctionKey::KEY_KP_ENTER;
	case GLFW_KEY_KP_EQUAL:				return FunctionKey::KEY_KP_EQUAL;
	case GLFW_KEY_LEFT_SHIFT:			return FunctionKey::KEY_LEFT_SHIFT;
	case GLFW_KEY_LEFT_CONTROL:			return FunctionKey::KEY_LEFT_CONTROL;
	case GLFW_KEY_LEFT_ALT:				return FunctionKey::KEY_LEFT_ALT;
	case GLFW_KEY_RIGHT_SHIFT:			return FunctionKey::KEY_RIGHT_SHIFT;
	case GLFW_KEY_RIGHT_CONTROL:		return FunctionKey::KEY_RIGHT_CONTROL;
	case GLFW_KEY_RIGHT_ALT:			return FunctionKey::KEY_RIGHT_ALT;
	default:							return FunctionKey::UNKOWN;
	}
}


