#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/DirectX/Resource/DirectXResourceChild.h>

NAMESPACE_MENGINE_BEGIN

class DirectXResource : public DirectXResourceChild
{
protected:
	DirectXResource(GraphicsObject* p_GraphicsResource);
public:
	virtual ~DirectXResource();

	inline ID3D11Resource* GetDirectXResource() const;
	inline ID3D11Resource* GetStagingResource() const;

	D3D11_MAPPED_SUBRESOURCE Map(ID3D11DeviceContext* context, _U32 a_SubResourceIndex);
	void Unmap(ID3D11DeviceContext* context, _U32 a_SubResourceIndex);

	virtual bool Update(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex) = 0;
	virtual bool Update(ID3D11DeviceContext* a_Context) = 0;
	virtual bool CopyMem2GraphMem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex) = 0;
	virtual bool CopyMem2GraphMem(ID3D11DeviceContext* a_Context) = 0;
	virtual bool CopyGraphMem2Mem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex) = 0;
	virtual bool CopyGraphMem2Mem(ID3D11DeviceContext* a_Context) = 0;
	virtual void CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target, _U32 a_SubResourceIndex) = 0;
	virtual void CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target) = 0;

protected:
	bool PreparedForCopy(D3D11_CPU_ACCESS_FLAG access) const;

protected:


	ID3D11Resource* m_Staging;

	static const UINT StagingAccess[];
};




inline ID3D11Resource* Miracle::DirectXResource::GetDirectXResource() const
{
	return static_cast<ID3D11Resource*>(m_Handle);
}

inline ID3D11Resource* Miracle::DirectXResource::GetStagingResource() const
{
	return m_Staging;
}

NAMESPACE_MENGINE_END