#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/RenderSystem/RenderSystem.h>
#include <Core/Application/GLFW/GLWindow.h>
#include <Core/Application/Windows/MSWindow.h>
#include <GamePlay/GameInstance.h>
#include <Independent/Timer/MTime.h>
#include <Core/Logging/MLog.h>
NAMESPACE_MENGINE_BEGIN


class MEngine
{
private:
	MEngine();

public:
	~MEngine();
	static MEngine* Instance();

	void StartUp();
	void ShutDown();

	// Render System Function
	void CreateRenderSystem(GLWindow* a_Handle);
	void CreateRenderSystem(MSWindow* a_Handle);
	inline RenderSystem* GetRenderSystem()
	{
		return m_RenderSystem;
	}

	// Game Instance Function
    void SetGameInstance(GameInstance* a_GameInstance);


	inline GameInstance* GetGameInstance()
	{
		return m_GameInstance;
	}

	void DoOneFrameUpdate();
private:
	static MEngine* s_pInstance;
	RenderSystem* m_RenderSystem;
	GameInstance* m_GameInstance;
	MTime m_Time;
};

NAMESPACE_MENGINE_END