#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureArray.h>
#include <Rendering/Base/Resource/Texture/TextureCubeArray.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTextureCubeArray : public DirectXTextureArray
{
public:
	DirectXTextureCubeArray(ID3D11Device* a_Device, TextureCubeArray* a_Texture);
	~DirectXTextureCubeArray();
	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline TextureCubeArray* GetTexture() const;
	inline ID3D11Texture2D* GetDirectTextureArray() const;
private:
	void CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
};

inline TextureCubeArray* DirectXTextureCubeArray::GetTexture() const
{
	return static_cast<TextureCubeArray*>(m_pGraphicsObject);
}

inline ID3D11Texture2D* DirectXTextureCubeArray::GetDirectTextureArray() const
{
	return static_cast<ID3D11Texture2D*>(m_Handle);
}

NAMESPACE_MENGINE_END
