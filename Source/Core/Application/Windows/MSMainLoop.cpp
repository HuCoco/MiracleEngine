#include <Core/Application/Windows/MSMainLoop.h>
#include <Core/Application/Base/Application.h>
#include <Core/Application/Windows/MSWindow.h>
#include <Core/Engine/MEngine.h>

NAMESPACE_MENGINE_BEGIN

MSMainLoop::MSMainLoop(Application* a_Application)
	:m_pApplication(a_Application)
{

}

MSMainLoop::~MSMainLoop()
{
}

void Miracle::MSMainLoop::Run()
{

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MEngine::Instance()->DoOneFrameUpdate();
		}

	}
}

NAMESPACE_MENGINE_END

