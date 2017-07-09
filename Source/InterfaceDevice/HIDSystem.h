#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <InterfaceDevice/KeyBoardManager.h>
#include <InterfaceDevice/MouseManager.h>

NAMESPACE_MENGINE_BEGIN

class HIDSystem
{
public:
	HIDSystem();
	~HIDSystem();

	static void StartUp();
	static void ShutDown();
	static HIDSystem* Instance();

public:
	KeyBoardManager KeyBoardState;
	MouseManager MouseState;

private:
	static HIDSystem* s_pInstance;
};

NAMESPACE_MENGINE_END