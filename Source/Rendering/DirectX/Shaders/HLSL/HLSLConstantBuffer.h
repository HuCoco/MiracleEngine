#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLBuffer.h>

NAMESPACE_MENGINE_BEGIN

class HLSLConstantBuffer : public HLSLBuffer
{
public:
	HLSLConstantBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_NumBytes, const std::vector<Member>& a_Members);
	HLSLConstantBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index, _U32 a_NumBytes, const std::vector<Member>& a_Members);
	virtual ~HLSLConstantBuffer();
};

NAMESPACE_MENGINE_END