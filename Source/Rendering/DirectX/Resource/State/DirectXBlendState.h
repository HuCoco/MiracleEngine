#pragma once
#include <Rendering/DirectX/Resource/State/DirectXState.h>
#include <Rendering/Base/Resource/State/BlendState.h>

NAMESPACE_MENGINE_BEGIN

class DirectXBlendState : public DirectXState
{
public:
	DirectXBlendState(ID3D11Device* device, BlendState* a_BlendState);
	virtual ~DirectXBlendState();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline BlendState* GetBlendState() const;
	inline ID3D11BlendState* GetD3DBlendState() const;

	void Enable(ID3D11DeviceContext* context);

private:

	static const D3D11_BLEND Mode[];
	static const D3D11_BLEND_OP Operation[];

};

inline BlendState* DirectXBlendState::GetBlendState() const
{
	return static_cast<BlendState*>(m_pGraphicsObject);
}

inline ID3D11BlendState* DirectXBlendState::GetD3DBlendState() const
{
	return static_cast<ID3D11BlendState*>(m_Handle);
}

NAMESPACE_MENGINE_END