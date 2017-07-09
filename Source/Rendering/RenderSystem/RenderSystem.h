#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/GraphicsEngine.h>
#include <Rendering/Base/Shaders/ProgramFactory.h>
#include <Rendering/RenderSystem/Renderer/BaseRenderer.h>
#include <Rendering/RenderSystem/VisualEffectManager.h>
#include <Core/Application/GLFW/GLWindow.h>
#include <Core/Application/Windows/MSWindow.h>

NAMESPACE_MENGINE_BEGIN

class RenderSystem
{
public:
	enum class RenderMode
	{
		ForwardRendering,
		DeferredRendering,
		DeferredLighting,
	};


	RenderSystem(GLWindow* a_Window);
	RenderSystem(MSWindow* a_Window);
	~RenderSystem();
	void CreateRenderer(RenderMode a_Mode);
	void RenderCurrentWorld();

	inline GraphicsEngine* GetRenderEngine()
	{
		return m_RenderEngine;
	}

	inline ProgramFactory* GetProgramFactory()
	{
		return m_ProgramFactory;
	}

	inline VisualEffectManager& GetVisualEffectManager()
	{
		return m_VisualEffectManager;
	}

	void RenderWorld();

private:
	VisualEffectManager m_VisualEffectManager;
	GraphicsEngine* m_RenderEngine;
	ProgramFactory* m_ProgramFactory;
	BaseRenderer* m_Renderer;
};

NAMESPACE_MENGINE_END