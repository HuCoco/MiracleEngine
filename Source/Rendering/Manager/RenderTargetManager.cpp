#include "RenderTargetManager.h"



Miracle::RenderTargetManager::RenderTargetManager()
{
}


Miracle::RenderTargetManager::~RenderTargetManager()
{
}

bool Miracle::RenderTargetManager::Insert(RenderTarget* a_RenderTarget, std::shared_ptr<RenderTargetResource> a_RenderTargetResource)
{
	return ResrouceMap.Insert(a_RenderTarget, a_RenderTargetResource);
}

bool Miracle::RenderTargetManager::Get(RenderTarget* a_RenderTarget, std::shared_ptr<RenderTargetResource>& a_RenderTargetResource) const
{
	auto node = ResrouceMap.Find(a_RenderTarget);
	if (node == nullptr)
	{
		return false;
	}
	a_RenderTargetResource = node->Value;
	return true;
}