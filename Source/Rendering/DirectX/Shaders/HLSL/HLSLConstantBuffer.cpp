#include <Rendering/DirectX/Shaders/HLSL/HLSLConstantBuffer.h>

Miracle::HLSLConstantBuffer::HLSLConstantBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_NumBytes, const std::vector<Member>& a_Members)
	: HLSLBuffer(a_Desc,a_NumBytes,a_Members)
{

}

Miracle::HLSLConstantBuffer::HLSLConstantBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index, _U32 a_NumBytes, const std::vector<Member>& a_Members)
	: HLSLBuffer(a_Desc,a_Index,a_NumBytes,a_Members)
{

}

Miracle::HLSLConstantBuffer::~HLSLConstantBuffer()
{

}
