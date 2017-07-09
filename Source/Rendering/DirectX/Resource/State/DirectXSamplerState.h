#pragma once
#include <Rendering/DirectX/Resource/State/DirectXState.h>
#include <Rendering/Base/Resource/State/SamplerState.h>

NAMESPACE_MENGINE_BEGIN

class DirectXSamplerState : public DirectXState
{
public:
	DirectXSamplerState(ID3D11Device* device, SamplerState* a_SamplerState);
	virtual ~DirectXSamplerState();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline SamplerState* GetSamplerState() const;
	inline ID3D11SamplerState* GetD3DSamplerState() const;

private:

	static D3D11_FILTER const Filter[];
	static D3D11_TEXTURE_ADDRESS_MODE const Mode[];
	static D3D11_COMPARISON_FUNC const Comparison[];
};

inline SamplerState* DirectXSamplerState::GetSamplerState() const
{
	return static_cast<SamplerState*>(m_pGraphicsObject);
}

inline ID3D11SamplerState* DirectXSamplerState::GetD3DSamplerState() const
{
	return static_cast<ID3D11SamplerState*>(m_Handle);
}

NAMESPACE_MENGINE_END