#pragma once
#include <Rendering/DirectX/Resource/State/DirectXState.h>
#include <Rendering/Base/Resource/State/RasterizerState.h>

NAMESPACE_MENGINE_BEGIN

class DirectXRasterizerState : public DirectXState
{
public:
	DirectXRasterizerState(ID3D11Device* device, RasterizerState* a_RasterizerState);
	virtual ~DirectXRasterizerState();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline RasterizerState* GetRasterizerState() const;
	inline ID3D11RasterizerState* GetD3DRasterizerState() const;

	void Enable(ID3D11DeviceContext* context);

private:

	static D3D11_FILL_MODE const FillMode[];
	static D3D11_CULL_MODE const CullMode[];
};

inline RasterizerState* DirectXRasterizerState::GetRasterizerState() const
{
	return static_cast<RasterizerState*>(m_pGraphicsObject);
}

inline ID3D11RasterizerState* DirectXRasterizerState::GetD3DRasterizerState() const
{
	return static_cast<ID3D11RasterizerState*>(m_Handle);
}

NAMESPACE_MENGINE_END