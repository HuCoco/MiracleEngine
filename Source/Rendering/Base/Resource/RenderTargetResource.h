#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/RenderTarget.h>

NAMESPACE_MENGINE_BEGIN

class RenderTargetResource
{
protected:
	RenderTargetResource(RenderTarget* a_RenderTarget);
public:
	~RenderTargetResource();
	inline RenderTarget* GetRenderTarget() const;
protected:
	RenderTarget* m_Target;
};

inline RenderTarget* RenderTargetResource::GetRenderTarget() const
{
	return m_Target;
}


NAMESPACE_MENGINE_END