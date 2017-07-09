#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLBuffer.h>

NAMESPACE_MENGINE_BEGIN

class HLSLResourceBindInfo : public HLSLBuffer
{
public:
	HLSLResourceBindInfo(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_NumBytes, const std::vector<Member>& a_Members);
	HLSLResourceBindInfo(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index, _U32 a_NumBytes, const std::vector<Member>& a_Members);
	~HLSLResourceBindInfo();
};

NAMESPACE_MENGINE_END