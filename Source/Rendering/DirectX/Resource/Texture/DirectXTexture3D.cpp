#include <Rendering/DirectX/Resource/Texture/DirectXTexture3D.h>


Miracle::DirectXTexture3D::DirectXTexture3D(ID3D11Device* a_Device,Texture3D* a_Texture)
	: DirectXTextureSingle(a_Texture)
{
	// Specify the texture description.
	D3D11_TEXTURE3D_DESC desc;
	desc.Width = a_Texture->GetWidth();
	desc.Height = a_Texture->GetHeight();
	desc.Depth = a_Texture->GetDepth();
	desc.MipLevels = a_Texture->GetNumLevels();
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
	ID3D11Texture3D* dxTexture = nullptr;
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
			data[index].SysMemSlicePitch = sr.SlicePitch;
		}
		hr = a_Device->CreateTexture3D(&desc, &data[0], &dxTexture);
	}
	else
	{
		hr = a_Device->CreateTexture3D(&desc, nullptr, &dxTexture);
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

Miracle::DirectXTexture3D::~DirectXTexture3D()
{
}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXTexture3D::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE3D)
	{
		return std::make_shared<DirectXTexture3D>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<Texture3D*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

void Miracle::DirectXTexture3D::CreateStaging(ID3D11Device* a_Device, const D3D11_TEXTURE3D_DESC& tx)
{
	D3D11_TEXTURE3D_DESC desc;
	desc.Width = tx.Width;
	desc.Height = tx.Height;
	desc.Depth = tx.Depth;
	desc.MipLevels = tx.MipLevels;
	desc.Format = tx.Format;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = D3D11_BIND_NONE;
	desc.CPUAccessFlags = StagingAccess[static_cast<_U32>(GetTexture()->GetAccessFlag())];
	desc.MiscFlags = D3D11_RESOURCE_MISC_NONE;

	HRESULT hr = a_Device->CreateTexture3D(&desc, nullptr,
		reinterpret_cast<ID3D11Texture3D**>(&m_Staging));
	CHECK_HR_RETURN_NONE("Failed to create staging texture");
}

void Miracle::DirectXTexture3D::CreateShaderResourceView(ID3D11Device* a_Device, const D3D11_TEXTURE3D_DESC& tx)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = tx.Format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	desc.Texture3D.MostDetailedMip = 0;
	desc.Texture3D.MipLevels = tx.MipLevels;
	HRESULT hr = a_Device->CreateShaderResourceView(GetDirectXTexture(), &desc, &m_ShaderResourceView);
	CHECK_HR_RETURN_NONE("Failed to create shader resource view");
}

void Miracle::DirectXTexture3D::CreateUnorderedAccessView(ID3D11Device* a_Device, const D3D11_TEXTURE3D_DESC& tx)
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
	desc.Format = tx.Format;
	desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
	desc.Texture3D.MipSlice = 0;
	desc.Texture3D.FirstWSlice = 0;
	desc.Texture3D.WSize = tx.Depth;
	HRESULT hr = a_Device->CreateUnorderedAccessView(GetDirectXTexture(), &desc, &m_UnorderedAccessView);
	CHECK_HR_RETURN_NONE("Failed to create unordered access view");
}
