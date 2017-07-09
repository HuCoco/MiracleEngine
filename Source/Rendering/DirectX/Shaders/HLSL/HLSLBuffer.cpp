#include <Rendering/DirectX/Shaders/HLSL/HLSLBuffer.h>

Miracle::HLSLBuffer::HLSLBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_NumBytes, const std::vector<Member>& a_Members)
	: HLSLResource(a_Desc,a_NumBytes)
	, m_Members(a_Members)
{

}

Miracle::HLSLBuffer::HLSLBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index, _U32 a_NumBytes, const std::vector<Member>& a_Members)
	: HLSLResource(a_Desc,a_Index,a_NumBytes)
	, m_Members(a_Members)
{

}

Miracle::HLSLBuffer::~HLSLBuffer()
{

}

std::vector<Miracle::HLSLBuffer::Member> const& Miracle::HLSLBuffer::GetMembers() const
{
	return m_Members;
}
