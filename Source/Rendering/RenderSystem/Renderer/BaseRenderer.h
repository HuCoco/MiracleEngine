#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/GraphicsEngine.h>
#include <GamePlay/World.h>
NAMESPACE_MENGINE_BEGIN

class BaseRenderer
{
public:
	BaseRenderer(GraphicsEngine* m_RenderEngine);
	~BaseRenderer();

	virtual void DoRender(World* a_World) = 0;

protected:
	GraphicsEngine* m_RenderEngine;
};

NAMESPACE_MENGINE_END