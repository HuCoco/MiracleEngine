#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/DirectXResource.h>
#include <Rendering/Base/Resource/Texture/Texture.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTexture : public DirectXResource
{
protected:
	DirectXTexture(Texture* a_Texture);
public:
	virtual ~DirectXTexture();

	inline Texture* GetTexture() const;
	inline ID3D11ShaderResourceView* GetShaderResourceView() const;
	inline ID3D11UnorderedAccessView* GetUnorderedAccessView() const;

	virtual bool Update(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex);
	virtual bool Update(ID3D11DeviceContext* a_Context);
	virtual bool CopyMem2GraphMem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex);
	virtual bool CopyMem2GraphMem(ID3D11DeviceContext* a_Context);
	virtual bool CopyGraphMem2Mem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex);
	virtual bool CopyGraphMem2Mem(ID3D11DeviceContext* a_Context);
	virtual void CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target, _U32 a_SubResourceIndex);
	virtual void CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target);
protected:

	static void CopyPitched2(_U32 numRows, _U32 srcRowPitch,
		const void* srcData, _U32 trgRowPitch, void* trgData);

	static void CopyPitched3(_U32 numRows, _U32 numSlices,
		_U32 srcRowPitch, _U32 srcSlicePitch,
		const void* srcData, _U32 trgRowPitch,
		_U32 trgSlicePitch, void* trgData);

	ID3D11ShaderResourceView* m_ShaderResourceView;
	ID3D11UnorderedAccessView* m_UnorderedAccessView;
};

inline Texture* DirectXTexture::GetTexture() const
{
	return static_cast<Texture*>(m_pGraphicsObject);
}

inline ID3D11ShaderResourceView* DirectXTexture::GetShaderResourceView() const
{
	return m_ShaderResourceView;
}

inline ID3D11UnorderedAccessView* DirectXTexture::GetUnorderedAccessView() const
{
	return m_UnorderedAccessView;
}


NAMESPACE_MENGINE_END