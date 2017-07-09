#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLResource.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLShaderVariable.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLShaderType.h>

NAMESPACE_MENGINE_BEGIN

class HLSLBuffer : public HLSLResource
{
public:
	typedef std::pair<HLSLShaderVariable, HLSLShaderType> Member;

	HLSLBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_NumBytes, const std::vector<Member>& a_Members);
	HLSLBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index, _U32 a_NumBytes, const std::vector<Member>& a_Members);

	virtual ~HLSLBuffer();

	// Member access.
	std::vector<Member> const& GetMembers() const;
private:
	std::vector<Member> m_Members;
};

NAMESPACE_MENGINE_END