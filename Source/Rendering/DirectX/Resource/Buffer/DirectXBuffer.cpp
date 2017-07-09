#include "DirectXBuffer.h"




Miracle::DirectXBuffer::DirectXBuffer(Buffer* a_Buffer)
	: DirectXResource(a_Buffer)
	, m_UpdateMapMode(D3D11_MAP_WRITE_DISCARD)
{

}

Miracle::DirectXBuffer::~DirectXBuffer()
{
}

bool Miracle::DirectXBuffer::Update(ID3D11DeviceContext* context)
{
	Buffer* buffer = GetBuffer();
	if (buffer->GetUsage() != GraphicsResource::Usage::DYNAMIC)
	{
		MENGINE_ASSERT_MSG(false, "Buffer is not Dynamic.");
		return false;
	}
	_U32 numActiveBytes = buffer->GetNumActiveBytes();
	if (numActiveBytes > 0)
	{
		ID3D11Buffer* dxBuffer = GetDirectXBuffer();
		D3D11_MAPPED_SUBRESOURCE sub;
		HRESULT hr = context->Map(dxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		if (hr != S_OK)
		{
			MENGINE_ASSERT_MSG(false, "Failed to map buffer.");
			return false;
		}

		if (m_UpdateMapMode != D3D11_MAP_WRITE_DISCARD)
		{
			_U32 offsetIndBytes = buffer->GetOffset() * buffer->GetElementSize();
			void* source = (char*)buffer->GetData() + offsetIndBytes;
			void* target = (char*)sub.pData + offsetIndBytes;
			memcpy(target, source, numActiveBytes);
		}
		else
		{
			memcpy(sub.pData, buffer->GetData(), buffer->GetNumBytes());
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Buffer has zero active bytes.");
	}
	return true;
}

bool Miracle::DirectXBuffer::Update(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex)
{
	MENGINE_ASSERT_MSG(false, "This was called polymorphically through DX11Resource.");
	return false;
}

bool Miracle::DirectXBuffer::CopyMem2GraphMem(ID3D11DeviceContext* a_Context)
{
	if (!PreparedForCopy(D3D11_CPU_ACCESS_READ))
	{
		return false;
	}

	Buffer* buffer = GetBuffer();
	UINT numActiveBytes = buffer->GetNumActiveBytes();
	if (numActiveBytes > 0)
	{
		unsigned int offsetInBytes = buffer->GetOffset() * buffer->GetElementSize();
		D3D11_BOX box = { offsetInBytes, 0, 0, offsetInBytes + numActiveBytes, 1, 1 };
		a_Context->CopySubresourceRegion(
			m_Staging, 0, offsetInBytes, 0, 0, GetDirectXBuffer(), 0, &box);

		D3D11_MAPPED_SUBRESOURCE sub;
		HRESULT hr = a_Context->Map(m_Staging, 0, D3D11_MAP_READ, 0, &sub);
		CHECK_HR_RETURN("Failed to map staging buffer", false);

		char const* source = (char*)sub.pData + offsetInBytes;
		void* target = (char*)buffer->GetData() + offsetInBytes;
		memcpy(target, source, numActiveBytes);
		a_Context->Unmap(m_Staging, 0);
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Buffer has zero active bytes.");
	}
	return true;
}

bool Miracle::DirectXBuffer::CopyMem2GraphMem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex)
{
	MENGINE_ASSERT_MSG(false,"TODO");
	return false;
}

bool Miracle::DirectXBuffer::CopyGraphMem2Mem(ID3D11DeviceContext* a_Context)
{
	if (!PreparedForCopy(D3D11_CPU_ACCESS_READ))
	{
		return false;
	}

	Buffer* buffer = GetBuffer();
	UINT numActiveBytes = buffer->GetNumActiveBytes();
	if (numActiveBytes > 0)
	{
		unsigned int offsetInBytes = buffer->GetOffset() * buffer->GetElementSize();
		D3D11_BOX box = { offsetInBytes, 0, 0, offsetInBytes + numActiveBytes, 1, 1 };
		a_Context->CopySubresourceRegion(m_Staging, 0, offsetInBytes, 0, 0, GetDirectXBuffer(), 0, &box);

		D3D11_MAPPED_SUBRESOURCE sub;
		HRESULT hr = a_Context->Map(m_Staging, 0, D3D11_MAP_READ, 0, &sub);
		CHECK_HR_RETURN("Failed to map staging buffer", false);

		char const* source = (char*)sub.pData + offsetInBytes;
		void* target = (char*)buffer->GetData() + offsetInBytes;
		memcpy(target, source, numActiveBytes);
		a_Context->Unmap(m_Staging, 0);
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Buffer has zero active bytes.");
	}
	return true;
}

bool Miracle::DirectXBuffer::CopyGraphMem2Mem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex)
{
	MENGINE_ASSERT_MSG(false, "TODO");
	return false;
}

void Miracle::DirectXBuffer::CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target)
{
	Buffer* buffer = GetBuffer();
	UINT numActiveBytes = buffer->GetNumActiveBytes();
	if (numActiveBytes > 0)
	{
		unsigned int offsetInBytes = buffer->GetOffset() * buffer->GetElementSize();
		D3D11_BOX box = { offsetInBytes, 0, 0, offsetInBytes + numActiveBytes, 1, 1 };
		a_Context->CopySubresourceRegion(
			a_Target, 0, offsetInBytes, 0, 0, GetDirectXBuffer(), 0, &box);
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Buffer has zero active bytes.");
	}
}

void Miracle::DirectXBuffer::CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target, _U32 a_SubResourceIndex)
{
	MENGINE_ASSERT_MSG(false, "TODO");
}
