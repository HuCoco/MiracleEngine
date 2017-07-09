#include "DirectXTextureDepthStencil.h"

Miracle::DirectXTextureDepthStencil::DirectXTextureDepthStencil(ID3D11Device* a_Device, TextureDepthStencil* a_Texture)
	: DirectXTexture2D(a_Texture)
{
	// Specify the texture description.
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = a_Texture->GetWidth();
	desc.Height = a_Texture->GetHeight();
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = GetDepthResourceFormat(static_cast<DXGI_FORMAT>(a_Texture->GetDataFormat()));
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	desc.MiscFlags = (a_Texture->IsShared() ?
		D3D11_RESOURCE_MISC_SHARED : D3D11_RESOURCE_MISC_NONE);
	if (a_Texture->IsShaderInput())
	{
		desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	}

	// Create the texture.  Depth-stencil textures are not initialized by
	// system memory data.
	ID3D11Texture2D* dxTexture = nullptr;
	HRESULT hr = a_Device->CreateTexture2D(&desc, nullptr, &dxTexture);
	CHECK_HR_RETURN_VOID("Failed to create depth-stencil texture");
	m_Handle = dxTexture;

	// Create a view of the texture.
	CreateDepthStencilView(a_Device);

	// Create a shader resource view if the depth-stencil is to be used as an
	// input to shaders.
	if (a_Texture->IsShaderInput())
	{
		CreateDepthStencilResourceView(a_Device);
	}

	// Create a staging texture if requested.
	if (a_Texture->GetAccessFlag() != GraphicsResource::AccessFlag::NONE)
	{
		CreateStaging(a_Device, desc);
	}
}

Miracle::DirectXTextureDepthStencil::DirectXTextureDepthStencil(ID3D11Device* a_Device, const DirectXTextureDepthStencil* a_DirectXSharedTexture)
	: DirectXTexture2D(a_DirectXSharedTexture->GetTexture())
	, m_DepthStencilView(nullptr)
{
	ID3D11Texture2D* dxShared = a_DirectXSharedTexture->CreateSharedDirectXResource(a_Device);
	m_Handle = dxShared;
	CreateDepthStencilView(a_Device);
}

Miracle::DirectXTextureDepthStencil::~DirectXTextureDepthStencil()
{
	FinalRelease(m_DepthStencilView);
}


std::shared_ptr<Miracle::RenderResource> Miracle::DirectXTextureDepthStencil::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE_DEPTH_STENCIL)
	{
		return std::make_shared<DirectXTextureDepthStencil>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<TextureDepthStencil*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}



void Miracle::DirectXTextureDepthStencil::CreateDepthStencilView(ID3D11Device* device)
{
	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	desc.Format = static_cast<DXGI_FORMAT>(GetTexture()->GetDataFormat());
	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc.Flags = 0;
	desc.Texture2D.MipSlice = 0;
	HRESULT hr = device->CreateDepthStencilView(GetDirectXTexture(), &desc, &m_DepthStencilView);
	CHECK_HR_RETURN_NONE("Failed to create depth-stencil view");
}

void Miracle::DirectXTextureDepthStencil::CreateDepthStencilResourceView(ID3D11Device* device)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = GetDepthStencilResourceViewFormat(static_cast<DXGI_FORMAT>(GetTexture()->GetDataFormat()));
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MostDetailedMip = 0;
	desc.Texture2D.MipLevels = 1;
	HRESULT hr = device->CreateShaderResourceView(GetDirectXTexture(), &desc, &m_ShaderResourceView);
	CHECK_HR_RETURN_NONE("Failed to create shader resource view");
}

DXGI_FORMAT Miracle::DirectXTextureDepthStencil::GetDepthStencilResourceViewFormat(DXGI_FORMAT a_DepthFormat)
{
	if (a_DepthFormat == DXGI_FORMAT_D16_UNORM)
	{
		return DXGI_FORMAT_R16_UNORM;
	}

	if (a_DepthFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
	{
		return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	}

	if (a_DepthFormat == DXGI_FORMAT_D32_FLOAT)
	{
		return DXGI_FORMAT_R32_FLOAT;
	}

	if (a_DepthFormat == DXGI_FORMAT_D32_FLOAT_S8X24_UINT)
	{
		return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
	}

	MENGINE_ASSERT_MSG(false,"Invalid depth format.");
	return DXGI_FORMAT_UNKNOWN;
}

DXGI_FORMAT Miracle::DirectXTextureDepthStencil::GetDepthResourceFormat(DXGI_FORMAT a_DepthFormat)
{
	if (a_DepthFormat == DXGI_FORMAT_D16_UNORM)
	{
		return DXGI_FORMAT_R16_TYPELESS;
	}

	if (a_DepthFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
	{
		return DXGI_FORMAT_R24G8_TYPELESS;
	}

	if (a_DepthFormat == DXGI_FORMAT_D32_FLOAT)
	{
		return DXGI_FORMAT_R32_TYPELESS;
	}

	if (a_DepthFormat == DXGI_FORMAT_D32_FLOAT_S8X24_UINT)
	{
		return DXGI_FORMAT_R32G8X24_TYPELESS;
	}

	MENGINE_ASSERT_MSG(false,"Invalid depth format.");
	return DXGI_FORMAT_UNKNOWN;
}
