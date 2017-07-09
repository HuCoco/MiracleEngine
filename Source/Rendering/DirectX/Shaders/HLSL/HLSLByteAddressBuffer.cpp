#include <Rendering/DirectX/Shaders/HLSL/HLSLByteAddressBuffer.h>

Miracle::HLSLByteAddressBuffer::HLSLByteAddressBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc)
	: HLSLResource(a_Desc,0)
	, m_GpuWritable(a_Desc.Type == D3D_SIT_UAV_RWBYTEADDRESS)
{

}

Miracle::HLSLByteAddressBuffer::HLSLByteAddressBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index)
	: HLSLResource(a_Desc,a_Index, 0)
	, m_GpuWritable(a_Desc.Type == D3D_SIT_UAV_RWBYTEADDRESS)
{

}

Miracle::HLSLByteAddressBuffer::~HLSLByteAddressBuffer()
{

}

bool Miracle::HLSLByteAddressBuffer::IsGpuWritable() const
{
	return m_GpuWritable;
}
