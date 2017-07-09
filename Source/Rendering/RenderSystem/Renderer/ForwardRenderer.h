#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/RenderSystem/Renderer/BaseRenderer.h>
NAMESPACE_MENGINE_BEGIN

class ForwardRenderer : public BaseRenderer
{
public:
	ForwardRenderer(GraphicsEngine* a_RenderEngine);
	~ForwardRenderer();
};

NAMESPACE_MENGINE_END