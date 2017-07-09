#include <Core/Event/GLFW/GLFWMessageLoop.h>
#include <Core/Application/GLFW/GLWindow.h>
#include <Core/Application/Base/Application.h>
#include <Core/Event/Base/EventSystem.h>
#include <Core/Event/Extensions/HIDEvent/HIDEvent.h>
#include <InterfaceDevice/HIDSystem.h>

Miracle::GLFWMessageLoop::GLFWMessageLoop()
{

}

Miracle::GLFWMessageLoop::~GLFWMessageLoop()
{

}

void Miracle::GLFWMessageLoop::WindowSizeCallback(GLFWwindow* a_hWnd, _I32 a_Width, _I32 a_Height)
{
	Application* app = Application::Instance();
	app->GetWindowHandle()->OnResize(a_Width, a_Height);


}

void Miracle::GLFWMessageLoop::KeyCallback(GLFWwindow* a_hWnd, _I32 a_Key, _I32 a_ScanCode, _I32 a_Action, _I32 a_Mods)
{
	auto& KeyBoardState = HIDSystem::Instance()->KeyBoardState;
	auto Key = KeyBoardState.GetFunctionKeyFromGLFW(a_Key);
	if (a_Action == GLFW_PRESS)
	{
		KeyBoardState.SetFunctionKeyState(Key, KeyBoardManager::FunctionKeyState::Down);
	}
	else if (a_Action == GLFW_RELEASE)
	{
		KeyBoardState.SetFunctionKeyState(Key, KeyBoardManager::FunctionKeyState::Up);
	}
	auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
	EventSystem::Instance()->ProcessEvent(Event);
}

void Miracle::GLFWMessageLoop::CharCallback(GLFWwindow* a_hWnd, _U32 a_CodePoint)
{

}

void Miracle::GLFWMessageLoop::ScrollCallback(GLFWwindow* a_hWnd, _D64 a_XOffset, _D64 a_YOffset)
{
	auto& MouseState = HIDSystem::Instance()->MouseState;
	//MouseState.SetScrollOffset(a_YOffset);
	auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
	EventSystem::Instance()->ProcessEvent(Event);
}

void Miracle::GLFWMessageLoop::CursorPosCallback(GLFWwindow* a_hWnd, _D64 a_XPos, _D64 a_YPos)
{
	auto& MouseState = HIDSystem::Instance()->MouseState;
	MouseState.SetPosition(static_cast<_U32>(a_XPos), static_cast<_U32>(a_YPos));
	auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
	EventSystem::Instance()->ProcessEvent(Event);
}

void Miracle::GLFWMessageLoop::MouseButtonCallback(GLFWwindow* a_hWnd, _I32 a_Button, _I32 a_Action, _I32 a_Mode)
{
	auto& MouseState = HIDSystem::Instance()->MouseState;
	if (a_Action == GLFW_PRESS)
	{
		switch (a_Button)
		{
		case GLFW_MOUSE_BUTTON_LEFT: 
		{
			MouseState.SetLeftButtonState(MouseManager::MouseButtonState::Down);
			break;
		}
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			MouseState.SetRightButtonState(MouseManager::MouseButtonState::Down);
			break;
		}
		}
	}
	else if (a_Action == GLFW_RELEASE)
	{
		switch (a_Button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			MouseState.SetLeftButtonState(MouseManager::MouseButtonState::Up);
			break;
		}
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			MouseState.SetRightButtonState(MouseManager::MouseButtonState::Up);
			break;
		}
		}
	}
	auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
	EventSystem::Instance()->ProcessEvent(Event);
}

void Miracle::GLFWMessageLoop::WindowPosCallback(GLFWwindow* a_hWnd, _I32 a_XPos, _I32 a_YPos)
{

}

void Miracle::GLFWMessageLoop::WindowCloseCallback(GLFWwindow* a_hWnd)
{

}
