#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
NAMESPACE_MENGINE_BEGIN


class GLFWMessageLoop
{
public:
	GLFWMessageLoop();
	~GLFWMessageLoop();

	static void WindowSizeCallback(GLFWwindow* a_hWnd, _I32 a_Width, _I32 a_Height);
	static void KeyCallback(GLFWwindow* a_hWnd, _I32 a_Key, _I32 a_ScanCode, _I32 a_Action, _I32 a_Mods);
	static void CharCallback(GLFWwindow* a_hWnd, _U32 a_CodePoint);
	static void ScrollCallback(GLFWwindow* a_hWnd, _D64 a_XOffset, _D64 a_YOffset);
	static void CursorPosCallback(GLFWwindow* a_hWnd, _D64 a_XPos, _D64 a_YPos);
	static void MouseButtonCallback(GLFWwindow* a_hWnd, _I32 a_Button, _I32 a_Action, _I32 a_Mode);
	static void WindowPosCallback(GLFWwindow* a_hWnd, _I32 a_XPos, _I32 a_YPos);
	static void WindowCloseCallback(GLFWwindow* a_hWnd);
};

NAMESPACE_MENGINE_END