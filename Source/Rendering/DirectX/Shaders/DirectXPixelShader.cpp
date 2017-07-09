#include <Rendering/DirectX/Shaders/DirectXPixelShader.h>


Miracle::DirectXPixelShader::DirectXPixelShader(ID3D11Device* a_Device, Shader* a_Shader)
	: DirectXShader(a_Shader)
{
	std::vector<unsigned char> const& code = a_Shader->GetCompiledCode();

	ID3D11ClassLinkage* linkage = nullptr;
	ID3D11PixelShader* dxShader = nullptr;
	HRESULT hr = a_Device->CreatePixelShader(&code[0], code.size(), linkage, &dxShader);
	CHECK_HR_RETURN_NONE("Failed to create pixel shader");

	m_Handle = dxShader;
}

Miracle::DirectXPixelShader::~DirectXPixelShader()
{

}

void Miracle::DirectXPixelShader::Enable(ID3D11DeviceContext* a_Context)
{
	if (m_Handle)
	{
		ID3D11ClassInstance* instances[1] = { nullptr };
		UINT numInstances = 0;
		ID3D11PixelShader* dxShader = static_cast<ID3D11PixelShader*>(m_Handle);
		a_Context->PSSetShader(dxShader, instances, numInstances);
	}
}

void Miracle::DirectXPixelShader::Disable(ID3D11DeviceContext* a_Context)
{
	if (m_Handle)
	{
		ID3D11ClassInstance* instances[1] = { nullptr };
		UINT numInstances = 0;
		ID3D11PixelShader* dxShader = nullptr;
		a_Context->PSSetShader(dxShader, instances, numInstances);
	}
}


std::shared_ptr<Miracle::RenderResource> Miracle::DirectXPixelShader::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::PIXEL_SHADER)
	{
		return std::make_shared<DirectXPixelShader>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<Shader*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
void Miracle::DirectXPixelShader::EnableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11Buffer* a_Buffer)
{
	if (m_Handle)
	{
		ID3D11Buffer* buffers[1] = { a_Buffer };
		a_Context->PSSetConstantBuffers(a_BindPoint, 1, buffers);
	}
}

void Miracle::DirectXPixelShader::DisableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11Buffer* buffers[1] = { nullptr };
		a_Context->PSSetConstantBuffers(a_BindPoint, 1, buffers);
	}
}

void Miracle::DirectXPixelShader::EnableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11ShaderResourceView* a_ShaderResourceView)
{
	if (m_Handle)
	{
		ID3D11ShaderResourceView* views[1] = { a_ShaderResourceView };
		a_Context->PSSetShaderResources(a_BindPoint, 1, views);
	}
}

void Miracle::DirectXPixelShader::DisableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11ShaderResourceView* views[1] = { nullptr };
		a_Context->PSSetShaderResources(a_BindPoint, 1, views);
	}
}

void Miracle::DirectXPixelShader::EnableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint,
	ID3D11UnorderedAccessView* a_UnorderedAccessView, _U32 a_InitialCount)
{
	if (m_Handle)
	{
		ID3D11UnorderedAccessView* uaViews[1] = { a_UnorderedAccessView };
		unsigned int initialCounts[1] = { a_InitialCount };
		a_Context->OMSetRenderTargetsAndUnorderedAccessViews(
			D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL, nullptr, nullptr,
			a_BindPoint, 1, uaViews, initialCounts);
	}
}

void Miracle::DirectXPixelShader::DisableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11UnorderedAccessView* uaViews[1] = { nullptr };
		unsigned int initialCounts[1] = { 0xFFFFFFFFu };
		a_Context->OMSetRenderTargetsAndUnorderedAccessViews(
			D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL, nullptr, nullptr,
			a_BindPoint, 1, uaViews, initialCounts);
	}
}

void Miracle::DirectXPixelShader::EnableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11SamplerState* a_SamplerState)
{
	if (m_Handle)
	{
		ID3D11SamplerState* states[1] = { a_SamplerState };
		a_Context->PSSetSamplers(a_BindPoint, 1, states);
	}
}

void Miracle::DirectXPixelShader::DisableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11SamplerState* states[1] = { nullptr };
		a_Context->PSSetSamplers(a_BindPoint, 1, states);
	}
}

