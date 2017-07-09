#pragma once
#include <Rendering/DirectX/Resource/State/DirectXState.h>
#include <Rendering/Base/Resource/State/DepthStencilState.h>

NAMESPACE_MENGINE_BEGIN

class DirectXDepthStencilState : public DirectXState
{
public:
	DirectXDepthStencilState(ID3D11Device* device, DepthStencilState* a_DepthStencilState);
	virtual ~DirectXDepthStencilState();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline DepthStencilState* GetDepthStencilState() const;
	inline ID3D11DepthStencilState* GetD3DDepthStencilState() const;

	void Enable(ID3D11DeviceContext* context);

private:

	static const D3D11_DEPTH_WRITE_MASK WriteMask[];
	static const D3D11_COMPARISON_FUNC Comparison[];
	static const D3D11_STENCIL_OP Operation[];
};

inline DepthStencilState* DirectXDepthStencilState::GetDepthStencilState() const
{
	return static_cast<DepthStencilState*>(m_pGraphicsObject);
}

inline ID3D11DepthStencilState* DirectXDepthStencilState::GetD3DDepthStencilState() const
{
	return static_cast<ID3D11DepthStencilState*>(m_Handle);
}


NAMESPACE_MENGINE_END