#include <Rendering/DirectX/Resource/Texture/DirectXTextureRenderTarget.h>


Miracle::DirectXTextureRenderTarget::DirectXTextureRenderTarget(ID3D11Device* a_Device, TextureRenderTarget* a_Texture)
	: DirectXTexture2D(a_Texture)
	, m_RenderTargetView(nullptr)
{
	// Specify the texture description.
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = a_Texture->GetWidth();
	desc.Height = a_Texture->GetHeight();
	desc.MipLevels = a_Texture->GetNumLevels();
	desc.ArraySize = 1;
	desc.Format = static_cast<DXGI_FORMAT>(a_Texture->GetDataFormat());
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	desc.MiscFlags = (a_Texture->IsShared() ?
		D3D11_RESOURCE_MISC_SHARED : D3D11_RESOURCE_MISC_NONE);

	if (a_Texture->GetUsage() == GraphicsResource::Usage::DEFAULT)
	{
		desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	}

	if (a_Texture->WantAutogenerateMipmaps() && !a_Texture->IsShared())
	{
		desc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	// Create the texture.
	ID3D11Texture2D* dxTexture = nullptr;
	HRESULT hr;
	if (a_Texture->GetDataFormat())
	{
		_U32 const numSubresources = a_Texture->GetNumSubresources();
		std::vector<D3D11_SUBRESOURCE_DATA> data(numSubresources);
		for (_U32 index = 0; index < numSubresources; ++index)
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
	CHECK_HR_RETURN_VOID("Failed to map create texture");
	m_Handle = dxTexture;

	// Create views of the texture.
	CreateShaderResourceView(a_Device, desc);
	CreateRenderTargetView(a_Device, desc);
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

Miracle::DirectXTextureRenderTarget::DirectXTextureRenderTarget(ID3D11Device* device, const DirectXTextureRenderTarget* a_DirectXSharedTexture)
	: DirectXTexture2D(a_DirectXSharedTexture->GetTexture())
	, m_RenderTargetView(nullptr) 
{
	ID3D11Texture2D* dxShared = a_DirectXSharedTexture->CreateSharedDirectXResource(device);
	m_Handle = dxShared;
	D3D11_TEXTURE2D_DESC desc;
	dxShared->GetDesc(&desc);
	CreateRenderTargetView(device, desc);
}

Miracle::DirectXTextureRenderTarget::~DirectXTextureRenderTarget()
{
	FinalRelease(m_RenderTargetView);
}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXTextureRenderTarget::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE_RENDER_TARGET)
	{
		return std::make_shared<DirectXTextureRenderTarget>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<TextureRenderTarget*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

void Miracle::DirectXTextureRenderTarget::CreateRenderTargetView(ID3D11Device* device, const D3D11_TEXTURE2D_DESC& tx)
{
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	desc.Format = tx.Format;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	HRESULT hr = device->CreateRenderTargetView(GetDirectXTexture(), &desc, &m_RenderTargetView);
	CHECK_HR_RETURN_NONE("Failed to create render-target view");
}
