#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureSingle.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTexture2D : public DirectXTextureSingle
{
public:
	DirectXTexture2D(ID3D11Device* a_Device, Texture2D* a_Texture);
	DirectXTexture2D(ID3D11Device* a_Device, DirectXTexture2D* a_DirectXSharedTexture);
	DirectXTexture2D(Texture2D* a_Texture, ID3D11Texture2D* a_DirectXTexture, ID3D11ShaderResourceView* a_ShaderResourceView);
	~DirectXTexture2D();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline Texture2D* GetTexture() const;
	inline ID3D11Texture2D* GetDirectXTexture() const;

protected:
	// Constructors for DX11TextureRT and DX11TextureDS.
	DirectXTexture2D(Texture2D* a_Texture);

protected:
	// Support for construction.
	ID3D11Texture2D* CreateSharedDirectXResource(ID3D11Device* a_Device) const;
	void CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
};

inline Texture2D* DirectXTexture2D::GetTexture() const
{
	return static_cast<Texture2D*>(m_pGraphicsObject);
}

inline ID3D11Texture2D* DirectXTexture2D::GetDirectXTexture() const
{
	return static_cast<ID3D11Texture2D*>(m_Handle);
}

NAMESPACE_MENGINE_END