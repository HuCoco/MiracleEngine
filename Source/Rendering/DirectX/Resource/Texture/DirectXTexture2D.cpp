#include <Rendering/DirectX/Resource/Texture/DirectXTexture2D.h>


Miracle::DirectXTexture2D::DirectXTexture2D(ID3D11Device* a_Device, Texture2D* a_Texture)
	: DirectXTextureSingle(a_Texture)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = a_Texture->GetWidth();
	desc.Height = a_Texture->GetHeight();
	desc.MipLevels = a_Texture->GetNumLevels();
	desc.ArraySize = 1;
	desc.Format = static_cast<DXGI_FORMAT>(a_Texture->GetDataFormat());
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = (a_Texture->IsShared() ?
		D3D11_RESOURCE_MISC_SHARED : D3D11_RESOURCE_MISC_NONE);
	GraphicsResource::Usage usage = a_Texture->GetUsage();
	if (usage == GraphicsResource::Usage::IMMUTABLE)
	{
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	}
	else if (usage == GraphicsResource::Usage::DYNAMIC)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else  // usage == Resource::SHADER_OUTPUT
	{
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	}

	if (a_Texture->WantAutogenerateMipmaps() && !a_Texture->IsShared())
	{
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
		desc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	// Create the texture.
	ID3D11Texture2D* dxTexture = nullptr;
	HRESULT hr;
	if (a_Texture->GetData())
	{
		unsigned int const numSubresources = a_Texture->GetNumSubresources();
		std::vector<D3D11_SUBRESOURCE_DATA> data(numSubresources);
		for (unsigned int index = 0; index < numSubresources; ++index)
		{
			auto sr = a_Texture->GetSubresource(index);
			data[index].pSysMem = sr.Data;
			data[index].SysMemPitch = sr.RowPitch;
			data[index].SysMemSlicePitch = 0;
		}
		hr = a_Device->CreateTexture2D(&desc, &data[0], &dxTexture);
	}
	else
	{
		hr = a_Device->CreateTexture2D(&desc, nullptr, &dxTexture);
	}
	CHECK_HR_RETURN_VOID("Failed to create texture");
	m_Handle = dxTexture;

	// Create views of the texture.
	CreateShaderResourceView(a_Device, desc);
	if (a_Texture->GetUsage() == GraphicsResource::Usage::DEFAULT)
	{
		CreateUnorderedAccessView(a_Device, desc);
	}

	// Create a staging texture if requested.
	if (a_Texture->GetAccessFlag() != GraphicsResource::AccessFlag::NONE)
	{
		CreateStaging(a_Device, desc);
	}

	// Generate mipmaps if requested.
	if (a_Texture->WantAutogenerateMipmaps() && m_ShaderResourceView)
	{
		ID3D11DeviceContext* context;
		a_Device->GetImmediateContext(&context);
		context->GenerateMips(m_ShaderResourceView);
		context->Release();
	}
}

Miracle::DirectXTexture2D::DirectXTexture2D(ID3D11Device* a_Device, DirectXTexture2D* a_DirectXSharedTexture)
	: DirectXTextureSingle(a_DirectXSharedTexture->GetTexture())
{
	ID3D11Texture2D* dxShared = a_DirectXSharedTexture->CreateSharedDirectXResource(a_Device);
	m_Handle = dxShared;

	// Create view of the shared texture.
	auto gtTexture = a_DirectXSharedTexture->GetTexture();
	D3D11_TEXTURE2D_DESC desc;
	dxShared->GetDesc(&desc);
	CreateShaderResourceView(a_Device, desc);
	if (gtTexture->GetUsage() == GraphicsResource::Usage::DEFAULT)
	{
		CreateUnorderedAccessView(a_Device, desc);
	}

	// Create a staging texture for the shared texture if the original texture
	// also has ones.
	if (gtTexture->GetAccessFlag() != GraphicsResource::AccessFlag::NONE)
	{
		CreateStaging(a_Device, desc);
	}
}

Miracle::DirectXTexture2D::DirectXTexture2D(Texture2D* a_Texture, ID3D11Texture2D* a_DirectXTexture, ID3D11ShaderResourceView* a_ShaderResourceView)
	: DirectXTextureSingle(a_Texture)
{
	m_Handle = a_DirectXTexture;
	m_ShaderResourceView = a_ShaderResourceView;
}

Miracle::DirectXTexture2D::DirectXTexture2D(Texture2D* a_Texture)
	: DirectXTextureSingle(a_Texture)
{

}

Miracle::DirectXTexture2D::~DirectXTexture2D()
{

}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXTexture2D::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE2D)
	{
		return std::make_shared<DirectXTexture2D>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<Texture2D*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

ID3D11Texture2D* Miracle::DirectXTexture2D::CreateSharedDirectXResource(ID3D11Device* a_Device) const
{
	IDXGIResource* resource = nullptr;
	HRESULT hr = m_Handle->QueryInterface(__uuidof(IDXGIResource), (void**)&resource);
	CHECK_HR_RETURN("QueryInterface failed", nullptr);

	HANDLE handle = nullptr;
	hr = resource->GetSharedHandle(&handle);
	resource->Release();
	CHECK_HR_RETURN("GetSharedHandle failed", nullptr);

	ID3D11Texture2D* dxShared = nullptr;
	hr = a_Device->OpenSharedResource(handle, __uuidof(ID3D11Texture2D), (void**)&dxShared);
	CHECK_HR_RETURN("OpenSharedResource failed", nullptr);
	return dxShared;
}

void Miracle::DirectXTexture2D::CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = tx.Width;
	desc.Height = tx.Height;
	desc.MipLevels = tx.MipLevels;
	desc.ArraySize = tx.ArraySize;
	desc.Format = tx.Format;
	desc.SampleDesc.Count = tx.SampleDesc.Count;
	desc.SampleDesc.Quality = tx.SampleDesc.Quality;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = D3D11_BIND_NONE;
	desc.CPUAccessFlags = StagingAccess[static_cast<_U32>(GetTexture()->GetAccessFlag())];
	desc.MiscFlags = D3D11_RESOURCE_MISC_NONE;

	HRESULT hr = a_Device->CreateTexture2D(&desc, nullptr, reinterpret_cast<ID3D11Texture2D**>(m_Staging));
	CHECK_HR_RETURN_NONE("Failed to create staging texture");
}
/*
void Miracle::DirectXTexture2D::CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = tx.Format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MostDetailedMip = 0;
	desc.Texture2D.MipLevels = tx.MipLevels;

	HRESULT hr = a_Device->CreateShaderResourceView(GetDirectXTexture(), &desc, &m_ShaderResourceView);
	CHECK_HR_RETURN_NONE("Failed to create shader resource view");
}
*/
void Miracle::DirectXTexture2D::CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE2D_DESC& tx)
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
	desc.Format = tx.Format;
	desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	HRESULT hr = a_Device->CreateUnorderedAccessView(GetDirectXTexture(), &desc, &m_UnorderedAccessView);
	CHECK_HR_RETURN_NONE("Failed to create unordered access view");
}
