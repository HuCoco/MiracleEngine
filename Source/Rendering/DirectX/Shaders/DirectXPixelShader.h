#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Shaders/Shader.h>
#include <Rendering/DirectX/Shaders/DirectXShader.h>

NAMESPACE_MENGINE_BEGIN

class DirectXPixelShader : public DirectXShader
{
public:
	DirectXPixelShader(ID3D11Device* a_Device, Shader* a_Shader);
	~DirectXPixelShader();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	// Calls to ID3D11DeviceContext::XSSetShader.
	virtual void Enable(ID3D11DeviceContext* a_Context) override;
	virtual void Disable(ID3D11DeviceContext* a_Context) override;

	// Calls to ID3D11DeviceContext::XSSetConstantBuffers.
	virtual void EnableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11Buffer* a_Buffer) override;
	virtual void DisableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) override;

	// Calls to ID3D11DeviceContext::XSSetShaderResources.
	virtual void EnableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11ShaderResourceView* a_ShaderResourceView) override;
	virtual void DisableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) override;

	// Calls to ID3D11DeviceContext::XSSetUnorderedAccessViews.
	virtual void EnableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11UnorderedAccessView* a_UnorderedAccessView, _U32 initialCount) override;
	virtual void DisableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) override;

	// Calls to ID3D11DeviceContext::XSSetSamplers.
	virtual void EnableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11SamplerState* a_SamplerState) override;
	virtual void DisableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) override;
};

NAMESPACE_MENGINE_END