#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Shaders/Shader.h>
#include <Rendering/DirectX/Resource/DirectXResourceChild.h>

NAMESPACE_MENGINE_BEGIN

class DirectXShader : public DirectXResourceChild
{
protected:
	DirectXShader(Shader* a_Shader);
public:
	~DirectXShader();

	// Calls to ID3D11DeviceContext::XSSetShader.
	virtual void Enable(ID3D11DeviceContext* a_Context) = 0;
	virtual void Disable(ID3D11DeviceContext* a_Context) = 0;

	// Calls to ID3D11DeviceContext::XSSetConstantBuffers.
	virtual void EnableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11Buffer* a_Buffer) = 0;
	virtual void DisableConstantBuffer(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) = 0;

	// Calls to ID3D11DeviceContext::XSSetShaderResources.
	virtual void EnableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11ShaderResourceView* a_ShaderResourceView) = 0;
	virtual void DisableShaderResourceView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) = 0;

	// Calls to ID3D11DeviceContext::XSSetUnorderedAccessViews.
	virtual void EnableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11UnorderedAccessView* a_UnorderedAccessView, _U32 a_InitialCount) = 0;
	virtual void DisableUnorderedAccessView(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) = 0;

	// Calls to ID3D11DeviceContext::XSSetSamplers.
	virtual void EnableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint, ID3D11SamplerState* a_SamplerState) = 0;
	virtual void DisableSampler(ID3D11DeviceContext* a_Context, _U32 a_BindPoint) = 0;
};

NAMESPACE_MENGINE_END