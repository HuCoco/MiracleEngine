#include "RenderSystem.h"
#include <Core/Engine/MEngine.h>
#include <GamePlay/WorldContext.h>
#include <Rendering/OpenGL/OpenGLEngine.h>
#include <Rendering/OpenGL/Shaders/GLSLProgramFactory.h>
#include <Rendering/DirectX/DirectXEngine.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLProgramFactory.h>
#include <Rendering/RenderSystem/Renderer/DeferredRenderer.h>



Miracle::RenderSystem::RenderSystem(MSWindow* a_Window)
{
	m_RenderEngine = new DirectXEngine(a_Window->GetHandle(),a_Window->GetWidth(),a_Window->GetHeight());
	m_ProgramFactory = new HLSLProgramFactory();
}

Miracle::RenderSystem::RenderSystem(GLWindow* a_Window)
{
	m_RenderEngine = new OpenGLEngine(a_Window->GetHandle());
	m_ProgramFactory = new GLSLProgramFactory();
}

void Miracle::RenderSystem::CreateRenderer(RenderMode a_Mode)
{
	m_Renderer = new DeferredRenderer(m_RenderEngine);
}


Miracle::RenderSystem::~RenderSystem()
{
	delete m_RenderEngine;
	delete m_ProgramFactory;
	delete m_Renderer;
}

void Miracle::RenderSystem::RenderWorld()
{
	m_RenderEngine->ClearBuffers();
	
	m_RenderEngine->DisplayColorBuffer(0);
}

void Miracle::RenderSystem::RenderCurrentWorld()
{
	World* CurrentWorld = MEngine::Instance()->GetGameInstance()->GetWorldContext()->GetCurrentWorld();
	m_Renderer->DoRender(CurrentWorld);
	CurrentWorld->GetLightManager().ClearLights();
}

