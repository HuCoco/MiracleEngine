#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureArray.h>
#include <Rendering/Base/Resource/Texture/Texture1DArray.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTexture1DArray : public DirectXTextureArray
{
public:
	DirectXTexture1DArray(ID3D11Device* a_Device, Texture1DArray* a_Texture);
	~DirectXTexture1DArray();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline Texture1DArray* GetTexture() const;
	inline ID3D11Texture1D* GetDirectTextureArray() const;

private:
	void CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx);
	void CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx);
	void CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx);
};

inline Texture1DArray* DirectXTexture1DArray::GetTexture() const
{
	return static_cast<Texture1DArray*>(m_pGraphicsObject);
}

inline ID3D11Texture1D* DirectXTexture1DArray::GetDirectTextureArray() const
{
	return static_cast<ID3D11Texture1D*>(m_Handle);
}

NAMESPACE_MENGINE_END