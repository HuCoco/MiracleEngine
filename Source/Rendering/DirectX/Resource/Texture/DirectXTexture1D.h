#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureSingle.h>
#include <Rendering/Base/Resource/Texture/Texture1D.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTexture1D : public DirectXTextureSingle
{
public:
	DirectXTexture1D(ID3D11Device* a_Device, Texture1D* a_Texture);
	virtual ~DirectXTexture1D();

	static std::shared_ptr<RenderResource> Create(void* a_Device,GraphicsObject* a_GraphicsResource);

	inline Texture1D* GetTexure() const;
	inline ID3D11Texture1D* GetDirectXTexture() const;

private:
	void CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx);
	void CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx);
	void CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx);
};

inline Texture1D* DirectXTexture1D::GetTexure() const
{
	return static_cast<Texture1D*>(m_pGraphicsObject);
}

inline ID3D11Texture1D* DirectXTexture1D::GetDirectXTexture() const
{
	return static_cast<ID3D11Texture1D*>(m_Handle);
}

NAMESPACE_MENGINE_END