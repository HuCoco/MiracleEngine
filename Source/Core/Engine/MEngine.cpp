#include "MEngine.h"
#include <Core/Application/GLFW/GLWindow.h>
#include <Core/Application/Windows/MSWindow.h>
#include <Core/Event/Base/EventSystem.h>
#include <InterfaceDevice/HIDSystem.h>
#include <ResourceManager/GameResourceSystem.h>
#include <Core/Logging/MLog.h>
#include <Core/Logging/MLogToFile.h>
#include <Core/Logging/MLogToOutputWindow.h>

Miracle::MEngine* Miracle::MEngine::s_pInstance = nullptr;

Miracle::MEngine::MEngine()
{
	MLogToOutputWindow* LogToOutputWindow = new MLogToOutputWindow(MLog::MLogListener::LISTEN_FOR_ALL);
	MLog::AddListener(LogToOutputWindow);
	MENGINE_LOG_INFORMATION("Logging System Start Up!");
}


Miracle::MEngine::~MEngine()
{
}

Miracle::MEngine* Miracle::MEngine::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new MEngine;
	}
	return s_pInstance;
}

void Miracle::MEngine::StartUp()
{
	EventSystem::StartUp();
	HIDSystem::StartUp();
	GameResourceSystem::StartUp();
}

void Miracle::MEngine::ShutDown()
{
	EventSystem::ShutDown();
	HIDSystem::ShutDown();
	GameResourceSystem::ShutDown();
}

void Miracle::MEngine::CreateRenderSystem(GLWindow* a_Handle)
{
	m_RenderSystem = new RenderSystem(a_Handle);
}

void Miracle::MEngine::CreateRenderSystem(MSWindow* a_Handle)
{
	m_RenderSystem = new RenderSystem(a_Handle);
}

void Miracle::MEngine::DoOneFrameUpdate()
{
	m_Time.Tick();
	if (m_GameInstance == nullptr)
	{
		MENGINE_ASSERT_MSG(false, "Maybe you forget to set game instance");
		return;
	}
	m_GameInstance->HandleOneFrame(static_cast<_F32>(m_Time.GetIntervalTime()));
}

void Miracle::MEngine::SetGameInstance(GameInstance* a_GameInstance)
{
	if (a_GameInstance != nullptr)
	{
		m_GameInstance = a_GameInstance;
		m_GameInstance->Initialize();
	}
}
