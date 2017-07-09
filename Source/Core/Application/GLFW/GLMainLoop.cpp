#include <Core/Application/GLFW/GLMainLoop.h>
#include <Core/Application/Base/Application.h>
#include <Core/Application/GLFW/GLWindow.h>
#include <Independent/Timer/MTime.h>
#include <Core/Engine/MEngine.h>

NAMESPACE_MENGINE_BEGIN

GLMainLoop::GLMainLoop(Application* a_Application)
	: m_pApplication(a_Application)
{
	
}

GLMainLoop::~GLMainLoop()
{
}

void Miracle::GLMainLoop::Run()
{
	auto pWnd = static_cast<GLWindow*>(Application::Instance()->GetWindowHandle());
	while (!glfwWindowShouldClose(pWnd->GetHandle()))
	{
		MEngine::Instance()->DoOneFrameUpdate();
		glfwPollEvents();
	}
}

NAMESPACE_MENGINE_END