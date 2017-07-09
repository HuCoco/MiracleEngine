#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureArray.h>
#include <Rendering/Base/Resource/Texture/Texture2DArray.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTexture2DArray : public DirectXTextureArray
{
public:
	DirectXTexture2DArray(ID3D11Device* a_Device, Texture2DArray* a_Texture);
	~DirectXTexture2DArray();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline Texture2DArray* GetTexture() const;
	inline ID3D11Texture2D* GetDirectTextureArray() const;

private:
	void CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
	void CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx);
};

inline Texture2DArray* DirectXTexture2DArray::GetTexture() const
{
	return static_cast<Texture2DArray*>(m_pGraphicsObject);
}

inline ID3D11Texture2D* DirectXTexture2DArray::GetDirectTextureArray() const
{
	return static_cast<ID3D11Texture2D*>(m_Handle);
}

NAMESPACE_MENGINE_END