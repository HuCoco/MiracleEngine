#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture2D.h>
#include <Rendering/Base/Resource/Texture/TextureRenderTarget.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTextureRenderTarget : public DirectXTexture2D
{
public:
	DirectXTextureRenderTarget(ID3D11Device* device, TextureRenderTarget* a_Texture);
	DirectXTextureRenderTarget(ID3D11Device* device, const DirectXTextureRenderTarget* a_DirectXSharedTexture);
	~DirectXTextureRenderTarget();

	static std::shared_ptr<RenderResource> Create(void* device, GraphicsObject* a_GraphicsResource);

	inline TextureRenderTarget* GetTextureRenderTarget() const;
	inline ID3D11RenderTargetView* GetRenderTargetView() const;

private:
	void CreateRenderTargetView(ID3D11Device* device, const D3D11_TEXTURE2D_DESC& tx);
	ID3D11RenderTargetView* m_RenderTargetView;
};

inline TextureRenderTarget* DirectXTextureRenderTarget::GetTextureRenderTarget() const
{
	return static_cast<TextureRenderTarget*>(m_pGraphicsObject);
}

inline ID3D11RenderTargetView* DirectXTextureRenderTarget::GetRenderTargetView() const
{
	return m_RenderTargetView;
}
NAMESPACE_MENGINE_END