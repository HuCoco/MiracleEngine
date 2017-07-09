#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Resource/RenderTargetResource.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureRenderTarget.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureDepthStencil.h>

NAMESPACE_MENGINE_BEGIN

class DirectXRenderTarget : public RenderTargetResource
{
public:
	DirectXRenderTarget(RenderTarget* a_RenderTarget, std::vector<DirectXTextureRenderTarget*>& a_RenderTargetTexures,
		DirectXTextureDepthStencil* a_DepthTargetTexure);
	virtual ~DirectXRenderTarget();
	static std::shared_ptr<RenderTargetResource> Create(RenderTarget* a_RenderTarget,
		std::vector<RenderResource*>& a_RenderTargetTextures, RenderResource* a_DepthTargetTextures);

	inline DirectXTextureRenderTarget* GetRenderTargetTexture(_U32 a_Index) const;
	inline DirectXTextureDepthStencil* GetDepthStencilTexture() const;

	void Enable(ID3D11DeviceContext* context);
	void Disable(ID3D11DeviceContext* context);
	void EnableDepthStencilBuffer(ID3D11DeviceContext* context);
	void DisableDepthStencilBuffer(ID3D11DeviceContext* context);
private:
	std::vector<DirectXTextureRenderTarget*> m_RenderTargetTextures;
	DirectXTextureDepthStencil* m_DepthStencilTexture;

	// Convenient storage for enable/disable of targets.
	std::vector<ID3D11RenderTargetView*> m_RenderTargetViews;
	ID3D11DepthStencilView* m_DepthStencilView;

	// Temporary storage during enable/disable of targets.
	D3D11_VIEWPORT m_SaveViewport;
	std::vector<ID3D11RenderTargetView*> m_SaveRenderTargetViews;
	ID3D11DepthStencilView* m_SaveDepthStencilView;
};

inline DirectXTextureRenderTarget* DirectXRenderTarget::GetRenderTargetTexture(_U32 a_Index) const
{
	return m_RenderTargetTextures[a_Index];
}

inline DirectXTextureDepthStencil* DirectXRenderTarget::GetDepthStencilTexture() const
{
	return m_DepthStencilTexture;
}

NAMESPACE_MENGINE_END