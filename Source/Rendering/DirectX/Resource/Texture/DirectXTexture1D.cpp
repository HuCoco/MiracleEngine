#include <Rendering/DirectX/Resource/Texture/DirectXTexture1D.h>


Miracle::DirectXTexture1D::DirectXTexture1D(ID3D11Device* a_Device, Texture1D* a_Texture)
	: DirectXTextureSingle(a_Texture)
{
	D3D11_TEXTURE1D_DESC desc;
	desc.Width = a_Texture->GetLength();
	desc.MipLevels = a_Texture->GetNumLevels();
	desc.ArraySize = 1;
	desc.Format = static_cast<DXGI_FORMAT>(a_Texture->GetDataFormat());
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_NONE;
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

	if (a_Texture->WantAutogenerateMipmaps())
	{
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
		desc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	// Create the texture.
	ID3D11Texture1D* dxTexture = nullptr;
	HRESULT hr;
	if (a_Texture->GetData())
	{
		unsigned int const numSubresources = a_Texture->GetNumSubresources();
		std::vector<D3D11_SUBRESOURCE_DATA> data(numSubresources);
		for (unsigned int index = 0; index < numSubresources; ++index)
		{
			auto sr = a_Texture->GetSubresource(index);
			data[index].pSysMem = sr.Data;
			data[index].SysMemPitch = 0;
			data[index].SysMemSlicePitch = 0;
		}
		hr = a_Device->CreateTexture1D(&desc, &data[0], &dxTexture);
	}
	else
	{
		hr = a_Device->CreateTexture1D(&desc, nullptr, &dxTexture);
	}
	CHECK_HR_RETURN_VOID("Failed to create texture");
	m_Handle = dxTexture;

	// Create views of the texture.
	CreateShaderResourceView(a_Device, desc);
	if (usage == GraphicsResource::Usage::DEFAULT)
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

Miracle::DirectXTexture1D::~DirectXTexture1D()
{

}


std::shared_ptr<Miracle::RenderResource> Miracle::DirectXTexture1D::Create(void* a_Device,GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE1D)
	{
		return std::make_shared<DirectXTexture1D>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<Texture1D*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

void Miracle::DirectXTexture1D::CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx)
{
	D3D11_TEXTURE1D_DESC desc;
	desc.Width = tx.Width;
	desc.MipLevels = tx.MipLevels;
	desc.ArraySize = tx.ArraySize;
	desc.Format = tx.Format;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = D3D11_BIND_NONE;
	desc.CPUAccessFlags = StagingAccess[static_cast<_U32>(GetTexture()->GetAccessFlag())];
	desc.MiscFlags = D3D11_RESOURCE_MISC_NONE;

	HRESULT hr = a_Device->CreateTexture1D(&desc, nullptr,
		reinterpret_cast<ID3D11Texture1D**>(&m_Staging));
	CHECK_HR_RETURN_NONE("Failed to create staging texture");
}

void Miracle::DirectXTexture1D::CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = tx.Format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
	desc.Texture1D.MostDetailedMip = 0;
	desc.Texture1D.MipLevels = tx.MipLevels;
	HRESULT hr = a_Device->CreateShaderResourceView(GetDirectXTexture(), &desc, &m_ShaderResourceView);
	CHECK_HR_RETURN_NONE("Failed to create shader resource view");
}

void Miracle::DirectXTexture1D::CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE1D_DESC& tx)
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
	desc.Format = tx.Format;
	desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
	desc.Texture1D.MipSlice = 0;
	HRESULT hr = a_Device->CreateUnorderedAccessView(GetDirectXTexture(), &desc, &m_UnorderedAccessView);
	CHECK_HR_RETURN_NONE("Failed to create unordered access view");
}
