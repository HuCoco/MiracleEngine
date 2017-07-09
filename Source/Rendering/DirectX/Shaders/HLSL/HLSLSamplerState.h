#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLResource.h>

NAMESPACE_MENGINE_BEGIN

class HLSLSamplerState : public HLSLResource
{
public:
	HLSLSamplerState(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc);
	HLSLSamplerState(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index);
	~HLSLSamplerState();
};

NAMESPACE_MENGINE_END