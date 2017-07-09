#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureSingle.h>
#include <Rendering/Base/Resource/Texture/Texture3D.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTexture3D : public DirectXTextureSingle
{
public:
	DirectXTexture3D(ID3D11Device* a_Device, Texture3D* a_Texture);
	~DirectXTexture3D();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline Texture3D* GetTexure() const;
	inline ID3D11Texture3D* GetDirectXTexture() const;

private:
	void CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE3D_DESC& tx);
	void CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE3D_DESC& tx);
	void CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE3D_DESC& tx);
};

inline Texture3D* DirectXTexture3D::GetTexure() const
{
	return static_cast<Texture3D*>(m_pGraphicsObject);
}

inline ID3D11Texture3D* DirectXTexture3D::GetDirectXTexture() const
{
	return static_cast<ID3D11Texture3D*>(m_Handle);
}
NAMESPACE_MENGINE_END