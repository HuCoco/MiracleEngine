#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureArray.h>
#include <Rendering/Base/Resource/Texture/TextureCube.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTextureCube : public DirectXTextureArray
{
public:
	DirectXTextureCube(ID3D11Device* a_Device, TextureCube* a_Texture);
	~DirectXTextureCube();
	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline TextureCube* GetTexture() const;
	inline ID3D11Texture2D* GetDirectTexture() const;

private:
	void CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
};

inline TextureCube* DirectXTextureCube::GetTexture() const
{
	return static_cast<TextureCube*>(m_pGraphicsObject);
}

inline ID3D11Texture2D* DirectXTextureCube::GetDirectTexture() const
{
	return static_cast<ID3D11Texture2D*>(m_Handle);
}


NAMESPACE_MENGINE_END