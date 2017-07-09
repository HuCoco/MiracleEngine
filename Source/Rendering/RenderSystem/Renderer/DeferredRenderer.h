#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/RenderSystem/Renderer/BaseRenderer.h>
#include <Rendering/Base/Resource/Texture/RenderTarget.h>
NAMESPACE_MENGINE_BEGIN

class DeferredRenderer : public BaseRenderer
{
public:
	DeferredRenderer(GraphicsEngine* a_RenderEngine);
	~DeferredRenderer();

	void Initialze();
	virtual void DoRender(World* a_World);

private:
	void GeometryPass(World* a_World);
	void LightingPass(World* a_World);

private:
	std::shared_ptr<RenderTarget> m_MainRenderTarget;
	std::shared_ptr<RenderTarget> m_TransparentRenderTarget;

	std::shared_ptr<IndexBuffer> m_QuadIndexBuffer;
	std::shared_ptr<VertexBuffer> m_QuadVertexBuffer;

	static _F32 s_QuadVertices[];
	static _U32 s_QuadIndices[];
};

NAMESPACE_MENGINE_END