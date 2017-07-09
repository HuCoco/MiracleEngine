#include <Rendering/DirectX/Resource/State/DirectXDepthStencilState.h>

USING_NAMESPACE_MENGINE

const D3D11_DEPTH_WRITE_MASK DirectXDepthStencilState::WriteMask[] =
{
	D3D11_DEPTH_WRITE_MASK_ZERO,
	D3D11_DEPTH_WRITE_MASK_ALL
};

const D3D11_COMPARISON_FUNC DirectXDepthStencilState::Comparison[] =
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

const D3D11_STENCIL_OP DirectXDepthStencilState::Operation[] =
{
	D3D11_STENCIL_OP_KEEP,
	D3D11_STENCIL_OP_ZERO,
	D3D11_STENCIL_OP_REPLACE,
	D3D11_STENCIL_OP_INCR_SAT,
	D3D11_STENCIL_OP_DECR_SAT,
	D3D11_STENCIL_OP_INVERT,
	D3D11_STENCIL_OP_INCR,
	D3D11_STENCIL_OP_DECR
};

DirectXDepthStencilState::DirectXDepthStencilState(ID3D11Device* device, DepthStencilState* a_DepthStencilState)
	: DirectXState(a_DepthStencilState)
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = (a_DepthStencilState->depthEnable ? TRUE : FALSE);
	desc.DepthWriteMask = WriteMask[a_DepthStencilState->writeMask];
	desc.DepthFunc = Comparison[a_DepthStencilState->comparison];
	desc.StencilEnable = (a_DepthStencilState->stencilEnable ? TRUE : FALSE);
	desc.StencilReadMask = a_DepthStencilState->stencilReadMask;
	desc.StencilWriteMask = a_DepthStencilState->stencilWriteMask;
	DepthStencilState::Face front = a_DepthStencilState->frontFace;
	desc.FrontFace.StencilFailOp = Operation[front.fail];
	desc.FrontFace.StencilDepthFailOp = Operation[front.depthFail];
	desc.FrontFace.StencilPassOp = Operation[front.pass];
	desc.FrontFace.StencilFunc = Comparison[front.comparison];
	DepthStencilState::Face back = a_DepthStencilState->backFace;
	desc.BackFace.StencilFailOp = Operation[back.fail];
	desc.BackFace.StencilDepthFailOp = Operation[back.depthFail];
	desc.BackFace.StencilPassOp = Operation[back.pass];
	desc.BackFace.StencilFunc = Comparison[back.comparison];

	ID3D11DepthStencilState* state = nullptr;
	HRESULT hr = device->CreateDepthStencilState(&desc, &state);
	CHECK_HR_RETURN_NONE("Failed to create depth-stencil state");
	m_Handle = state;
}

DirectXDepthStencilState::~DirectXDepthStencilState()
{

}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXDepthStencilState::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::DEPTH_STENCIL_STATE)
	{
		return std::make_shared<DirectXDepthStencilState>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<DepthStencilState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

void DirectXDepthStencilState::Enable(ID3D11DeviceContext* context)
{
	DepthStencilState* dsState = GetDepthStencilState();
	context->OMSetDepthStencilState(GetD3DDepthStencilState(), dsState->reference);
}
