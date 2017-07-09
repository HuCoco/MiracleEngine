#include <Rendering/DirectX/Resource/State/DirectXRasterizerState.h>

const D3D11_FILL_MODE Miracle::DirectXRasterizerState::FillMode[] =
{
	D3D11_FILL_SOLID,
	D3D11_FILL_WIREFRAME
};

const D3D11_CULL_MODE Miracle::DirectXRasterizerState::CullMode[] =
{
	D3D11_CULL_NONE,
	D3D11_CULL_FRONT,
	D3D11_CULL_BACK
};


Miracle::DirectXRasterizerState::DirectXRasterizerState(ID3D11Device* device, RasterizerState* a_RasterizerState)
	:DirectXState(a_RasterizerState)
{
	D3D11_RASTERIZER_DESC desc;
	desc.FillMode = FillMode[a_RasterizerState->fillMode];
	desc.CullMode = CullMode[a_RasterizerState->cullMode];
	desc.FrontCounterClockwise = (a_RasterizerState->frontCCW ? TRUE : FALSE);
	desc.DepthBias = a_RasterizerState->depthBias;
	desc.DepthBiasClamp = a_RasterizerState->depthBiasClamp;
	desc.SlopeScaledDepthBias = a_RasterizerState->slopeScaledDepthBias;
	desc.DepthClipEnable = (a_RasterizerState->enableDepthClip ? TRUE : FALSE);
	desc.ScissorEnable = (a_RasterizerState->enableScissor ? TRUE : FALSE);
	desc.MultisampleEnable = (a_RasterizerState->enableMultisample ? TRUE : FALSE);
	desc.AntialiasedLineEnable = (a_RasterizerState->enableAntialiasedLine ? TRUE : FALSE);

	// Create the rasterizer state.
	ID3D11RasterizerState* state = nullptr;
	HRESULT hr = device->CreateRasterizerState(&desc, &state);
	CHECK_HR_RETURN_NONE("Failed to create rasterizer state");
	m_Handle = state;
}

Miracle::DirectXRasterizerState::~DirectXRasterizerState()
{

}

void Miracle::DirectXRasterizerState::Enable(ID3D11DeviceContext* context)
{
	context->RSSetState(GetD3DRasterizerState());
}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXRasterizerState::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::RASTERIZER_STATE)
	{
		return std::make_shared<DirectXRasterizerState>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<RasterizerState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
