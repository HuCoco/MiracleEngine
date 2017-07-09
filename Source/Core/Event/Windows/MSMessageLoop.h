#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <windows.h>

NAMESPACE_MENGINE_BEGIN

class MSMessageLoop
{
public:
	MSMessageLoop();
	~MSMessageLoop();

	static LRESULT CALLBACK MainEventLoop(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

};

NAMESPACE_MENGINE_END