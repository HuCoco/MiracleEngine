#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture2D.h>
#include <Rendering/Base/Resource/Texture/TextureDepthStencil.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTextureDepthStencil : public DirectXTexture2D
{
public:
	DirectXTextureDepthStencil(ID3D11Device* a_Device, TextureDepthStencil* a_Texture);
	DirectXTextureDepthStencil(ID3D11Device* a_Device, const DirectXTextureDepthStencil* a_DirectXSharedTexture);
	~DirectXTextureDepthStencil();

	static std::shared_ptr<RenderResource> Create(void* a_Device,GraphicsObject* a_GraphicsResource);

	inline TextureDepthStencil* GetTextureDepthStencil() const;
	inline ID3D11DepthStencilView* GetDepthStencilView() const;

private:
	void CreateDepthStencilView(ID3D11Device* device);
	void CreateDepthStencilResourceView(ID3D11Device* device);
	DXGI_FORMAT GetDepthResourceFormat(DXGI_FORMAT depthFormat);
	DXGI_FORMAT GetDepthStencilResourceViewFormat(DXGI_FORMAT depthFormat);

private:
	ID3D11DepthStencilView* m_DepthStencilView;
};

inline TextureDepthStencil* DirectXTextureDepthStencil::GetTextureDepthStencil() const
{
	return static_cast<TextureDepthStencil*>(m_pGraphicsObject);
}

inline ID3D11DepthStencilView* DirectXTextureDepthStencil::GetDepthStencilView() const
{
	return m_DepthStencilView;
}
NAMESPACE_MENGINE_END