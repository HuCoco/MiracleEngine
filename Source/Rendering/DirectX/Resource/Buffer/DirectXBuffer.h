#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/Buffer.h>
#include <Rendering/DirectX/Resource/DirectXResource.h>

NAMESPACE_MENGINE_BEGIN

class DirectXBuffer : public DirectXResource
{
protected:
	DirectXBuffer(Buffer* a_Buffer);
	virtual ~DirectXBuffer();
public:
	inline Buffer* GetBuffer() const;
	inline ID3D11Buffer* GetDirectXBuffer() const;


	virtual bool Update(ID3D11DeviceContext* context) override;
	virtual bool CopyMem2GraphMem(ID3D11DeviceContext* a_Context) override;
	virtual bool CopyGraphMem2Mem(ID3D11DeviceContext* a_Context) override;
	virtual void CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target) override;

private:
	virtual bool Update(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex) override;
	virtual bool CopyMem2GraphMem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex) override;
	virtual bool CopyGraphMem2Mem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex) override;
	virtual void CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target, _U32 a_SubResourceIndex) override;
private:
	D3D11_MAP m_UpdateMapMode;
};

inline Buffer* DirectXBuffer::GetBuffer() const
{
	return static_cast<Buffer*>(m_pGraphicsObject);
}

inline ID3D11Buffer* DirectXBuffer::GetDirectXBuffer() const
{
	return static_cast<ID3D11Buffer*>(m_Handle);
}

NAMESPACE_MENGINE_END 