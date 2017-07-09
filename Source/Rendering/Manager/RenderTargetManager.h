#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/RenderTargetResource.h>
#include <Rendering/Base/Resource/Texture/RenderTarget.h>
#include <Independent/DataStructure/MSet.h>

NAMESPACE_MENGINE_BEGIN

class RenderTargetManager
{
public:
	RenderTargetManager();
	~RenderTargetManager();

	bool Insert(RenderTarget* a_RenderTarget, std::shared_ptr<RenderTargetResource> a_RenderTargetResource);
	bool Get(RenderTarget* a_RenderTarget, std::shared_ptr<RenderTargetResource>& a_RenderTargetResource) const;

private:
	MSet<RenderTarget*, std::shared_ptr<RenderTargetResource>> ResrouceMap;
};

NAMESPACE_MENGINE_END