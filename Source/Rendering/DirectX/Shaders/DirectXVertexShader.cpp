#include <Rendering/DirectX/Shaders/DirectXVertexShader.h>



Miracle::DirectXVertexShader::DirectXVertexShader(ID3D11Device* a_Device, Shader* a_Shader)
	: DirectXShader(a_Shader)
{
	const std::vector<unsigned char>& code = a_Shader->GetCompiledCode();

	ID3D11ClassLinkage* linkage = nullptr;
	ID3D11VertexShader* dxShader = nullptr;
	HRESULT hr = a_Device->CreateVertexShader(&code[0], code.size(), linkage, &dxShader);
	CHECK_HR_RETURN_NONE("Failed to create vertex shader");

	m_Handle = dxShader;
}

Miracle::DirectXVertexShader::~DirectXVertexShader()
{
}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXVertexShader::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::VERTEX_SHADER)
	{
		return std::make_shared<DirectXVertexShader>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<Shader*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

void Miracle::DirectXVertexShader::Enable(ID3D11DeviceContext* a_Context)
{
	if (m_Handle)
	{
		ID3D11ClassInstance* instances[1] = { nullptr };
		UINT numInstances = 0;
		ID3D11VertexShader* dxShader = static_cast<ID3D11VertexShader*>(m_Handle);
		a_Context->VSSetShader(dxShader, instances, numInstances);
	}
}

void Miracle::DirectXVertexShader::Disable(ID3D11DeviceContext* a_Context)
{
	if (m_Handle)
	{
		ID3D11ClassInstance* instances[1] = { nullptr };
		UINT numInstances = 0;
		ID3D11VertexShader* dxShader = nullptr;
		a_Context->VSSetShader(dxShader, instances, numInstances);
	}
}

void Miracle::DirectXVertexShader::EnableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11Buffer* a_Buffer)
{
	if (m_Handle)
	{
		ID3D11Buffer* buffers[1] = { a_Buffer };
		a_Context->VSSetConstantBuffers(a_BindPoint, 1, buffers);
	}
}

void Miracle::DirectXVertexShader::DisableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11Buffer* buffers[1] = { nullptr };
		a_Context->VSSetConstantBuffers(a_BindPoint, 1, buffers);
	}
}

void Miracle::DirectXVertexShader::EnableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11ShaderResourceView* a_ShaderResourceView)
{
	if (m_Handle)
	{
		ID3D11ShaderResourceView* views[1] = { a_ShaderResourceView };
		a_Context->VSSetShaderResources(a_BindPoint, 1, views);
	}
}

void Miracle::DirectXVertexShader::DisableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11ShaderResourceView* views[1] = { nullptr };
		a_Context->VSSetShaderResources(a_BindPoint, 1, views);
	}
}

void Miracle::DirectXVertexShader::EnableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11UnorderedAccessView* a_UnorderedAccessView, _U32 a_InitialCount)
{
	if (m_Handle)
	{
		ID3D11Device* device = nullptr;
		a_Context->GetDevice(&device);
		if (!device)
		{
			MENGINE_ASSERT_MSG(false, "Cannot access device of context.");
			return;
		}

		if (device->GetFeatureLevel() == D3D_FEATURE_LEVEL_11_1)
		{
			ID3D11UnorderedAccessView* uaViews[1] = { a_UnorderedAccessView };
			unsigned int initialCounts[1] = { a_InitialCount };
			a_Context->OMSetRenderTargetsAndUnorderedAccessViews(
				D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL, nullptr,
				nullptr, a_BindPoint, 1, uaViews, initialCounts);
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "D3D11.1 is required for UAVs in vertex shaders.");
		}
		device->Release();
	}
}

void Miracle::DirectXVertexShader::DisableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11Device* device = nullptr;
		a_Context->GetDevice(&device);
		if (!device)
		{
			MENGINE_ASSERT_MSG(false,"Cannot access device of context.");
			return;
		}

		if (device->GetFeatureLevel() == D3D_FEATURE_LEVEL_11_1)
		{
			ID3D11UnorderedAccessView* uaViews[1] = { nullptr };
			unsigned int initialCounts[1] = { 0xFFFFFFFFu };
			a_Context->OMSetRenderTargetsAndUnorderedAccessViews(
				D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL, nullptr,
				nullptr, a_BindPoint, 1, uaViews, initialCounts);
		}
		else
		{
			MENGINE_ASSERT_MSG(false,"D3D11.1 is required for UAVs in vertex shaders.");
		}
		device->Release();
	}
}

void Miracle::DirectXVertexShader::EnableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11SamplerState* a_SamplerState)
{
	if (m_Handle)
	{
		ID3D11SamplerState* states[1] = { a_SamplerState };
		a_Context->VSSetSamplers(a_BindPoint, 1, states);
	}
}

void Miracle::DirectXVertexShader::DisableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint)
{
	if (m_Handle)
	{
		ID3D11SamplerState* states[1] = { nullptr };
		a_Context->VSSetSamplers(a_BindPoint, 1, states);
	}
}
