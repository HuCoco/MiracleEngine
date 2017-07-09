#include <Rendering/DirectX/Resource/State/DirectXBlendState.h>

const D3D11_BLEND Miracle::DirectXBlendState::Mode[] =
{
	D3D11_BLEND_ZERO,
	D3D11_BLEND_ONE,
	D3D11_BLEND_SRC_COLOR,
	D3D11_BLEND_INV_SRC_COLOR,
	D3D11_BLEND_SRC_ALPHA,
	D3D11_BLEND_INV_SRC_ALPHA,
	D3D11_BLEND_DEST_ALPHA,
	D3D11_BLEND_INV_DEST_ALPHA,
	D3D11_BLEND_DEST_COLOR,
	D3D11_BLEND_INV_DEST_COLOR,
	D3D11_BLEND_SRC_ALPHA_SAT,
	D3D11_BLEND_BLEND_FACTOR,
	D3D11_BLEND_INV_BLEND_FACTOR,
	D3D11_BLEND_SRC1_COLOR,
	D3D11_BLEND_INV_SRC1_COLOR,
	D3D11_BLEND_SRC1_ALPHA,
	D3D11_BLEND_INV_SRC1_ALPHA
};

const D3D11_BLEND_OP Miracle::DirectXBlendState::Operation[] =
{
	D3D11_BLEND_OP_ADD,
	D3D11_BLEND_OP_SUBTRACT,
	D3D11_BLEND_OP_REV_SUBTRACT,
	D3D11_BLEND_OP_MIN,
	D3D11_BLEND_OP_MAX
};

Miracle::DirectXBlendState::DirectXBlendState(ID3D11Device* device, BlendState* a_BlendState)
	: DirectXState(a_BlendState)
{

	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = (a_BlendState->enableAlphaToCoverage ? TRUE : FALSE);
	desc.IndependentBlendEnable = (a_BlendState->enableIndependentBlend ? TRUE : FALSE);
	for (_U32 i = 0; i < BlendState::NUM_TARGETS; ++i)
	{
		D3D11_RENDER_TARGET_BLEND_DESC& output = desc.RenderTarget[i];
		BlendState::Target const& input = a_BlendState->target[i];
		output.BlendEnable = (input.enable ? TRUE : FALSE);
		output.SrcBlend = Mode[input.srcColor];
		output.DestBlend = Mode[input.dstColor];
		output.BlendOp = Operation[input.opColor];
		output.SrcBlendAlpha = Mode[input.srcAlpha];
		output.DestBlendAlpha = Mode[input.dstAlpha];
		output.BlendOpAlpha = Operation[input.opAlpha];
		output.RenderTargetWriteMask = input.mask;
	}


	ID3D11BlendState* state = nullptr;
	HRESULT hr = device->CreateBlendState(&desc, &state);
	CHECK_HR_RETURN_NONE("Failed to create blend state");
	m_Handle = state;
}

Miracle::DirectXBlendState::~DirectXBlendState()
{

}

void Miracle::DirectXBlendState::Enable(ID3D11DeviceContext* context)
{
	BlendState* State = GetBlendState();
	context->OMSetBlendState(GetD3DBlendState(), &State->blendColor[0], State->sampleMask);
}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXBlendState::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::BLEND_STATE)
	{
		return std::make_shared<DirectXBlendState>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<BlendState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

