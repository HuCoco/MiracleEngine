#include <Core/Application/Base/Application.h>
#include <Core/Application/Windows/MSMainLoop.h>
#include <Core/Application/Windows/MSWindow.h>
#include <Core/Application/GLFW/GLMainLoop.h>
#include <Core/Application/GLFW/GLWindow.h>
#include <Core/Application/Base/Command.h>
#include <Core/Engine/MEngine.h>

#define GET_GL_WINDOW_HANDLE static_cast<GLWindow*>(Application::Instance()->GetWindowHandle())
#define GET_MS_WINDOW_HANDLE static_cast<MSWindow*>(Application::Instance()->GetWindowHandle())

NAMESPACE_MENGINE_BEGIN

volatile Application* Application::s_pInstance = new Application();


Application::Application()
{
	InitializeCommand();
	MEngine::Instance()->StartUp();
}


Application::~Application()
{
	delete m_Command;
}

void Application::Run()
{
	m_pMainLoop->Run();
}

void Application::ShutDown()
{
	MEngine::Instance()->ShutDown();
}

void Application::InitializeCommand()
{
	CREATE_COMMAND_ARRAY_BEGIN
		CREATE_COMMAND_ARRAY_DATA("dx", 0),
	CREATE_COMMAND_ARRAY_END
	m_Command = new Command();
	m_Command->AddCommand(g_CommandArgsList,ARRAY_SIZE_OF(g_CommandArgsList));
}

void Miracle::Application::ConfigureCommandLine(char* a_cmd)
{
	m_Command->ProcessingCommand(std::string(a_cmd), ',');
}

Application* Application::Instance()
{
	MENGINE_ASSERT_MSG(s_pInstance != nullptr, "Application Instance is Null");
	return const_cast<Application*>(s_pInstance);
}

void Application::Initialize()
{
	if (m_Command->IsThisCommand(1 << 0))
	{
		m_pWindow = new MSWindow();
		m_pWindow->SetTitle("MiracleEngine MSWindow");
		m_pMainLoop = new MSMainLoop(this);
		m_pWindow->Initialze();
		m_Setting.RenderMode = ApplicationSetting::AppRenderMode::DirectX11;
		MEngine::Instance()->CreateRenderSystem(GET_MS_WINDOW_HANDLE);
	}
	else
	{
		m_pWindow = new GLWindow();
		m_pWindow->SetTitle("MiracleEngine GLEWWindow");
		m_pMainLoop = new GLMainLoop(this);
		m_pWindow->Initialze();
		m_Setting.RenderMode = ApplicationSetting::AppRenderMode::OpenGL;
		MEngine::Instance()->CreateRenderSystem(GET_GL_WINDOW_HANDLE);
	}

	MEngine::Instance()->GetRenderSystem()->CreateRenderer(RenderSystem::RenderMode::DeferredRendering);

}


NAMESPACE_MENGINE_END