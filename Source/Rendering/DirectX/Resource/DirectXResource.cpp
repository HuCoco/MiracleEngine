#include <Rendering/DirectX/Resource/DirectXResource.h>

const UINT Miracle::DirectXResource::StagingAccess[] =
{
	D3D11_CPU_ACCESS_NONE,				// NONE,
	D3D11_CPU_ACCESS_READ,				// READ_ONLY,
	D3D11_CPU_ACCESS_WRITE,         	// WRITE_ONLY,
	D3D11_CPU_ACCESS_READ_WRITE     	// READ_WIRTE
};


Miracle::DirectXResource::DirectXResource(GraphicsObject* p_GraphicsResource)
	: DirectXResourceChild(p_GraphicsResource)
	, m_Staging(nullptr)
{

}

Miracle::DirectXResource::~DirectXResource()
{
	m_Handle->Release();
	m_Handle = nullptr;
}

D3D11_MAPPED_SUBRESOURCE Miracle::DirectXResource::Map(ID3D11DeviceContext* context, _U32 a_SubResourceIndex)
{
	D3D11_MAPPED_SUBRESOURCE mapped;
	HRESULT hr = context->Map(GetDirectXResource(), a_SubResourceIndex, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(hr))
	{
		mapped.pData = nullptr;
		mapped.RowPitch = 0;
		mapped.DepthPitch = 0;
	}
	return mapped;
}

void Miracle::DirectXResource::Unmap(ID3D11DeviceContext* context, _U32 a_SubResourceIndex)
{
	context->Unmap(GetDirectXResource(), a_SubResourceIndex);
}

bool Miracle::DirectXResource::PreparedForCopy(D3D11_CPU_ACCESS_FLAG access) const
{

	if (!m_Handle)
	{
		MENGINE_ASSERT_MSG(false,"Resource does not exist.");
		return false;
	}
	if (!m_Staging)
	{
		MENGINE_ASSERT_MSG(false,"Staging resource does not exist.");
		return false;
	}

	// Verify the copy type.
	_U32 index = static_cast<_U32>(GetGraphicsResource()->GetAccessFlag());
	if ((StagingAccess[index] & access) == 0)
	{
		MENGINE_ASSERT_MSG(false,"Staging resource has incorrect CPU access.");
		return false;
	}

	return true;
}

