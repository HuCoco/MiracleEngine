#include <Rendering/DirectX/Resource/Texture/DirectXTexture.h>

Miracle::DirectXTexture::DirectXTexture(Texture* a_Texture)
	: DirectXResource(a_Texture)
	, m_ShaderResourceView(nullptr)
	, m_UnorderedAccessView(nullptr)
{

}

Miracle::DirectXTexture::~DirectXTexture()
{
	FinalRelease(m_ShaderResourceView);
	FinalRelease(m_UnorderedAccessView);
}

bool Miracle::DirectXTexture::Update(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex)
{
	Texture* texture = GetTexture();
	if (a_SubResourceIndex >= texture->GetNumSubresources())
	{
		MENGINE_ASSERT_MSG(false,"Subresource index out of range.");
		return false;
	}

	if (texture->GetUsage() != GraphicsResource::Usage::DYNAMIC)
	{
		MENGINE_ASSERT_MSG(false,"Texture usage is not DYNAMIC_UPDATE.");
		return false;
	}

	ID3D11Resource* dxTexture = GetDirectXResource();
	D3D11_MAPPED_SUBRESOURCE sub;
	HRESULT hr = a_Context->Map(dxTexture, a_SubResourceIndex, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	CHECK_HR_RETURN("Failed to map staging texture", false);

	auto sr = texture->GetSubresource(a_SubResourceIndex);
	_U32 numDimensions = texture->GetNumDimensions();
	if (numDimensions == 1)
	{
		memcpy(sub.pData, sr.Data, texture->GetNumBytesByLevel(sr.Level));
	}
	else if (numDimensions == 2)
	{
		CopyPitched2(texture->GetDimensionByLevel(sr.Level, 1), sr.RowPitch,
			sr.Data, sub.RowPitch, sub.pData);
	}
	else 
	{
		CopyPitched3(texture->GetDimensionByLevel(sr.Level, 1),
			texture->GetDimensionByLevel(sr.Level, 2), sr.RowPitch, sr.SlicePitch,
			sr.Data, sub.RowPitch, sub.DepthPitch, sub.pData);
	}
	a_Context->Unmap(dxTexture, a_SubResourceIndex);
	return true;
}

bool Miracle::DirectXTexture::Update(ID3D11DeviceContext* a_Context)
{
	Texture* texture = GetTexture();
	const _U32 numSubresources = texture->GetNumSubresources();
	for (_U32 index = 0; index < numSubresources; ++index)
	{
		if (!Update(a_Context, index))
		{
			return false;
		}
	}
	return true;
}

bool Miracle::DirectXTexture::CopyMem2GraphMem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex)
{
	Texture* texture = GetTexture();
	if (a_SubResourceIndex >= texture->GetNumSubresources())
	{
		MENGINE_ASSERT_MSG(false,"Subresource index out of range.");
		return false;
	}

	if (!PreparedForCopy(D3D11_CPU_ACCESS_WRITE))
	{
		return false;
	}

	// Map the staging texture.
	D3D11_MAPPED_SUBRESOURCE sub;
	HRESULT hr = a_Context->Map(m_Staging, a_SubResourceIndex, D3D11_MAP_WRITE, 0, &sub);
	CHECK_HR_RETURN("Failed to map staging texture", false);

	// Copy from CPU memory to staging texture.
	auto sr = texture->GetSubresource(a_SubResourceIndex);
	_U32 numDimensions = texture->GetNumDimensions();
	if (numDimensions == 1)
	{
		memcpy(sub.pData, sr.Data, texture->GetNumBytesByLevel(sr.Level));
	}
	else if (numDimensions == 2)
	{
		CopyPitched2(texture->GetDimensionByLevel(sr.Level, 1), sr.RowPitch,
			sr.Data, sub.RowPitch, sub.pData);
	}
	else  // numDimensions == 3
	{
		CopyPitched3(texture->GetDimensionByLevel(sr.Level, 1),
			texture->GetDimensionByLevel(sr.Level, 2), sr.RowPitch,
			sr.SlicePitch, sr.Data, sub.RowPitch, sub.DepthPitch,
			sub.pData);
	}
	a_Context->Unmap(m_Staging, a_SubResourceIndex);

	// Copy from staging texture to GPU memory.
	ID3D11Resource* dxTexture = GetDirectXResource();
	a_Context->CopySubresourceRegion(dxTexture, a_SubResourceIndex, 0, 0, 0, m_Staging, a_SubResourceIndex, nullptr);
	return true;
}

bool Miracle::DirectXTexture::CopyMem2GraphMem(ID3D11DeviceContext* a_Context)
{
	Texture* texture = GetTexture();
	const _U32 numSubresources = texture->GetNumSubresources();
	for (_U32 index = 0; index < numSubresources; ++index)
	{
		if (!CopyMem2GraphMem(a_Context, index))
		{
			return false;
		}
	}

	// Generate mipmaps (when they exist).
	if (texture->WantAutogenerateMipmaps() && m_ShaderResourceView)
	{
		a_Context->GenerateMips(m_ShaderResourceView);
	}
	return true;
}

bool Miracle::DirectXTexture::CopyGraphMem2Mem(ID3D11DeviceContext* a_Context, _U32 a_SubResourceIndex)
{
	Texture* texture = GetTexture();
	if (a_SubResourceIndex >= texture->GetNumSubresources())
	{
		MENGINE_ASSERT_MSG(false,"Subresource index out of range.");
		return false;
	}

	if (!PreparedForCopy(D3D11_CPU_ACCESS_READ))
	{
		return false;
	}

	// Copy from GPU memory to staging texture.
	ID3D11Resource* dxTexture = GetDirectXResource();
	a_Context->CopySubresourceRegion(m_Staging, a_SubResourceIndex, 0, 0, 0, dxTexture, a_SubResourceIndex, nullptr);

	// Map the staging texture.
	D3D11_MAPPED_SUBRESOURCE sub;
	HRESULT hr = a_Context->Map(m_Staging, a_SubResourceIndex, D3D11_MAP_READ, 0, &sub);
	CHECK_HR_RETURN("Failed to map staging texture", false);

	// Copy from staging texture to CPU memory.
	auto sr = texture->GetSubresource(a_SubResourceIndex);
	_U32 numDimensions = texture->GetNumDimensions();
	if (numDimensions == 1)
	{
		memcpy(sr.Data, sub.pData, texture->GetNumBytesByLevel(sr.Level));
	}
	else if (numDimensions == 2)
	{
		CopyPitched2(texture->GetDimensionByLevel(sr.Level, 1), sub.RowPitch,
			sub.pData, sr.RowPitch, sr.Data);
	}
	else  // numDimensions == 3
	{
		CopyPitched3(texture->GetDimensionByLevel(sr.Level, 1),
			texture->GetDimensionByLevel(sr.Level, 2), sub.RowPitch,
			sub.DepthPitch, sub.pData, sr.RowPitch, sr.SlicePitch, sr.Data);
	}
	a_Context->Unmap(m_Staging, a_SubResourceIndex);
	return true;
}

bool Miracle::DirectXTexture::CopyGraphMem2Mem(ID3D11DeviceContext* a_Context)
{
	Texture* texture = GetTexture();
	const _U32 numSubresources = texture->GetNumSubresources();
	for (_U32 index = 0; index < numSubresources; ++index)
	{
		if (!CopyGraphMem2Mem(a_Context, index))
		{
			return false;
		}
	}
	return true;
}

void Miracle::DirectXTexture::CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target, _U32 a_SubResourceIndex)
{
	Texture* texture = GetTexture();
	if (a_SubResourceIndex >= texture->GetNumSubresources())
	{
		MENGINE_ASSERT_MSG(false,"Subresource index out of range.");
		return;
	}

	// Copy from GPU memory to staging texture.
	ID3D11Resource* dxTexture = GetDirectXResource();
	a_Context->CopySubresourceRegion(a_Target, a_SubResourceIndex, 0, 0, 0, dxTexture, a_SubResourceIndex, nullptr);
}

void Miracle::DirectXTexture::CopyGraphMem2GraphMem(ID3D11DeviceContext* a_Context, ID3D11Resource* a_Target)
{
	Texture* texture = GetTexture();
	const _U32 numSubresources = texture->GetNumSubresources();
	for (_U32 index = 0; index < numSubresources; ++index)
	{
		CopyGraphMem2GraphMem(a_Context, a_Target, index);
	}
}

void Miracle::DirectXTexture::CopyPitched2(_U32 numRows, _U32 srcRowPitch, const void* srcData, _U32 trgRowPitch, void* trgData)
{
	if (srcRowPitch == trgRowPitch)
	{
		// The memory is contiguous.
		memcpy(trgData, srcData, trgRowPitch*numRows);
	}
	else
	{
		// Padding was added to each row of the texture, so we must
		// copy a row at a time to compensate for differing pitches.
		_U32 numRowBytes = min(srcRowPitch, trgRowPitch);
		const char* srcRow = static_cast<const char*>(srcData);
		char* trgRow = static_cast<char*>(trgData);
		for (_U32 row = 0; row < numRows; ++row)
		{
			memcpy(trgRow, srcRow, numRowBytes);
			srcRow += srcRowPitch;
			trgRow += trgRowPitch;
		}
	}
}

void Miracle::DirectXTexture::CopyPitched3(_U32 numRows, _U32 numSlices,
	_U32 srcRowPitch, _U32 srcSlicePitch, const void* srcData,
	_U32 trgRowPitch, _U32 trgSlicePitch, void* trgData)
{
	if (srcRowPitch == trgRowPitch && srcSlicePitch == trgSlicePitch)
	{
		// The memory is contiguous.
		memcpy(trgData, srcData, trgSlicePitch*numSlices);
	}
	else
	{
		// Padding was added to each row and/or slice of the texture, so
		// we must copy the data to compensate for differing pitches.
		unsigned int numRowBytes = min(srcRowPitch, trgRowPitch);
		char const* srcSlice = static_cast<char const*>(srcData);
		char* trgSlice = static_cast<char*>(trgData);
		for (unsigned int slice = 0; slice < numSlices; ++slice)
		{
			char const* srcRow = srcSlice;
			char* trgRow = trgSlice;
			for (unsigned int row = 0; row < numRows; ++row)
			{
				memcpy(trgRow, srcRow, numRowBytes);
				srcRow += srcRowPitch;
				trgRow += trgRowPitch;
			}
			srcSlice += srcSlicePitch;
			trgSlice += trgSlicePitch;
		}
	}
}

