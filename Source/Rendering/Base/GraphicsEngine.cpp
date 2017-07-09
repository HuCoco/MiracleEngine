#include <Rendering/Base/GraphicsEngine.h>



Miracle::GraphicsEngine::GraphicsEngine()
{

}


Miracle::GraphicsEngine::~GraphicsEngine()
{
}

Miracle::RenderResource* Miracle::GraphicsEngine::Bind(const std::shared_ptr<GraphicsObject>& a_Object)
{
	if (!a_Object)
	{
		MENGINE_ASSERT_MSG(false, "This Object is null.");
		return nullptr;
	}

	GraphicsResource* pGraphicsResource = static_cast<GraphicsResource*>(a_Object.get());
	std::shared_ptr<RenderResource> pRenderResource;
	if (!m_ResourceMananger.Get(pGraphicsResource, pRenderResource))
	{
		CreateRenderResource Creator = m_RenderResourceCreators[a_Object->GetType()];
		if (!Creator)
		{
			MENGINE_ASSERT_MSG(false, "This Creator is missing.");
			return nullptr;
		}

		pRenderResource = Creator(m_CreatorDevice,pGraphicsResource);
		MENGINE_ASSERT_MSG(pRenderResource, "RenderResource create fail!");
		m_ResourceMananger.Insert(pGraphicsResource, pRenderResource);

	}
	return pRenderResource.get();
}

Miracle::RenderTargetResource* Miracle::GraphicsEngine::Bind(const std::shared_ptr<RenderTarget>& target)
{
	RenderTarget* gtTarget = target.get();
	std::shared_ptr<RenderTargetResource> geTarget;
	if (!m_RenderTargetMananger.Get(gtTarget, geTarget))
	{
		unsigned int const numTargets = target->GetNumTargets();
		std::vector<RenderResource*> rtTextures(numTargets);
		for (unsigned int i = 0; i < numTargets; ++i)
		{
			rtTextures[i] = static_cast<RenderResource*>(Bind(target->GetRTTexture(i)));
		}

		std::shared_ptr<TextureDepthStencil> object = target->GetDSTexture();
		RenderResource* dsTexture;
		if (object)
		{
			dsTexture = static_cast<RenderResource*>(Bind(object));
		}
		else
		{
			dsTexture = nullptr;
		}

		geTarget = m_RenderTargetResourceCreator(gtTarget, rtTextures, dsTexture);
		m_RenderTargetMananger.Insert(gtTarget, geTarget);
	}
	return geTarget.get();
}

Miracle::RenderResource* Miracle::GraphicsEngine::Get(const std::shared_ptr<GraphicsObject>& a_Object) const
{
	GraphicsResource* pGraphicsResource = static_cast<GraphicsResource*>(a_Object.get());
	std::shared_ptr<RenderResource> pRenderResource;
	if (m_ResourceMananger.Get(pGraphicsResource, pRenderResource))
	{
		return pRenderResource.get();
	}
	return nullptr;
}

Miracle::RenderTargetResource* Miracle::GraphicsEngine::Get(const std::shared_ptr<RenderTarget>& target) const
{
	RenderTarget* gtTarget = target.get();
	std::shared_ptr<RenderTargetResource> geTarget;
	if (!m_RenderTargetMananger.Get(gtTarget, geTarget))
	{
		MENGINE_ASSERT_MSG(false,"Cannot find draw target.");
	}
	return geTarget.get();
}

