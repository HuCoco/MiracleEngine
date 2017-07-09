#include <Core/Event/Windows/MSMessageLoop.h>
#include <Core/Application/Base/Application.h>
#include <Core/Application/Base/BaseWindow.h>
#include <InterfaceDevice/HIDSystem.h>
#include <Core/Event/Extensions/HIDEvent/HIDEvent.h>
#include <Core/Event/Base/EventSystem.h>
#include <Rendering/Base/GraphicsEngine.h>

Miracle::MSMessageLoop::MSMessageLoop()
{

}

Miracle::MSMessageLoop::~MSMessageLoop()
{
}
 
LRESULT CALLBACK Miracle::MSMessageLoop::MainEventLoop(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{

	case WM_SIZE:
	{
		Application* app = Application::Instance();
		app->GetWindowHandle()->OnResize(LOWORD(lparam), HIWORD(lparam));
		
	} 
	break;

	case WM_LBUTTONUP:
	{
		auto& MouseState = HIDSystem::Instance()->MouseState;
		MouseState.SetLeftButtonState(MouseManager::MouseButtonState::Up);
	} 
	break;

	case WM_LBUTTONDOWN:
	{
		auto& MouseState = HIDSystem::Instance()->MouseState;
		MouseState.SetLeftButtonState(MouseManager::MouseButtonState::Up);
	}
	break;

	//case WM_MBUTTONUP:
	//{

	//}
	//break;

	//case WM_MBUTTONDOWN:
	//{

	//}
	//break;

	case WM_RBUTTONUP:
	{
		auto& MouseState = HIDSystem::Instance()->MouseState;
		MouseState.SetRightButtonState(MouseManager::MouseButtonState::Up);
	} 
	break;

	case WM_RBUTTONDOWN:
	{
		auto& MouseState = HIDSystem::Instance()->MouseState;
		MouseState.SetRightButtonState(MouseManager::MouseButtonState::Down);
	}
	break;

	case WM_MOUSEMOVE:
	{
		auto& MouseState = HIDSystem::Instance()->MouseState;
		MouseState.SetPosition(static_cast<_U32>(LOWORD(lparam)), static_cast<_U32>(HIWORD(lparam)));
		auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
		EventSystem::Instance()->ProcessEvent(Event);
	} 
	break;

	case WM_MOUSEWHEEL:
	{
		auto& MouseState = HIDSystem::Instance()->MouseState;
		//MouseState.SetScrollOffset(LOWORD(lparam));
		auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
		EventSystem::Instance()->ProcessEvent(Event);
	}
	break;

	case WM_CHAR:
	{

	} 
	break;

	case WM_KEYDOWN:
	{
		auto& KeyBoardState = HIDSystem::Instance()->KeyBoardState;
		auto Key = KeyBoardState.GetFunctionKeyFromMS(wparam);
		KeyBoardState.SetFunctionKeyState(Key, KeyBoardManager::FunctionKeyState::Down);
		auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
		EventSystem::Instance()->ProcessEvent(Event);
	} 
	break;

	case WM_KEYUP:
	{
		auto& KeyBoardState = HIDSystem::Instance()->KeyBoardState;
		auto Key = KeyBoardState.GetFunctionKeyFromMS(wparam);
		KeyBoardState.SetFunctionKeyState(Key, KeyBoardManager::FunctionKeyState::Up);
		auto Event = std::make_shared<HIDEvent>(HIDSystem::Instance());
		EventSystem::Instance()->ProcessEvent(Event);
	} 
	break;

	case WM_CREATE:
	{
		return(0);
	} 
	break;

	case WM_PAINT:
	{
	} 
	break;

	case WM_CLOSE:
	{

	} 
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return(0);
	} 
	break;
	}
	return(DefWindowProc(hwnd, msg, wparam, lparam));

}
