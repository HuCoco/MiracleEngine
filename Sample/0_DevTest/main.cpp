#include <windows.h>
#include <Core/Application/Base/Application.h>
#include <Core/Engine/MEngine.h>
#include "DefaultGameInstance.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Miracle::Application* app = Miracle::Application::Instance();
	DefaultGameInstance* TestGame = new DefaultGameInstance;
	Miracle::MEngine::Instance()->SetGameInstance(TestGame);
	app->ConfigureCommandLine(lpCmdLine);
	app->Initialize();
	app->Run();
	return 0;
}