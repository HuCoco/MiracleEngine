#include <Rendering/DirectX/Resource/State/DirectXSamplerState.h>

const D3D11_FILTER Miracle::DirectXSamplerState::Filter[] =
{
	D3D11_FILTER_MIN_MAG_MIP_POINT,
	D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,
	D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
	D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,
	D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,
	D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
	D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
	D3D11_FILTER_MIN_MAG_MIP_LINEAR,
	D3D11_FILTER_ANISOTROPIC,
	D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
	D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
	D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
	D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
	D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
	D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
	D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
	D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
	D3D11_FILTER_COMPARISON_ANISOTROPIC
};

const D3D11_TEXTURE_ADDRESS_MODE Miracle::DirectXSamplerState::Mode[] =
{
	D3D11_TEXTURE_ADDRESS_WRAP,
	D3D11_TEXTURE_ADDRESS_MIRROR,
	D3D11_TEXTURE_ADDRESS_CLAMP,
	D3D11_TEXTURE_ADDRESS_BORDER,
	D3D11_TEXTURE_ADDRESS_MIRROR_ONCE
};

const D3D11_COMPARISON_FUNC Miracle::DirectXSamplerState::Comparison[] =
{
	D3D11_COMPARISON_NEVER,
	D3D11_COMPARISON_LESS,
	D3D11_COMPARISON_EQUAL,
	D3D11_COMPARISON_LESS_EQUAL,
	D3D11_COMPARISON_GREATER,
	D3D11_COMPARISON_NOT_EQUAL,
	D3D11_COMPARISON_GREATER_EQUAL,
	D3D11_COMPARISON_ALWAYS
};


Miracle::DirectXSamplerState::DirectXSamplerState(ID3D11Device* device, SamplerState* a_SamplerState)
	: DirectXState(a_SamplerState)
{
	D3D11_SAMPLER_DESC desc;
	desc.Filter = Filter[a_SamplerState->filter];
	desc.AddressU = Mode[a_SamplerState->mode[0]];
	desc.AddressV = Mode[a_SamplerState->mode[1]];
	desc.AddressW = Mode[a_SamplerState->mode[2]];
	desc.MipLODBias = a_SamplerState->mipLODBias;
	desc.MaxAnisotropy = a_SamplerState->maxAnisotropy;
	desc.ComparisonFunc = Comparison[a_SamplerState->comparison];
	desc.BorderColor[0] = a_SamplerState->borderColor[0];
	desc.BorderColor[1] = a_SamplerState->borderColor[1];
	desc.BorderColor[2] = a_SamplerState->borderColor[2];
	desc.BorderColor[3] = a_SamplerState->borderColor[3];
	desc.MinLOD = a_SamplerState->minLOD;
	desc.MaxLOD = a_SamplerState->maxLOD;

	// Create the sampler state.
	ID3D11SamplerState* state = nullptr;
	HRESULT hr = device->CreateSamplerState(&desc, &state);
	CHECK_HR_RETURN_NONE("Failed to create sampler state");
	m_Handle = state;
}


Miracle::DirectXSamplerState::~DirectXSamplerState()
{

}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXSamplerState::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::SAMPLER_STATE)
	{
		return std::make_shared<DirectXSamplerState>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<SamplerState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

