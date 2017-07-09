#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLResource.h>

NAMESPACE_MENGINE_BEGIN

class HLSLByteAddressBuffer : public HLSLResource
{
public:
	HLSLByteAddressBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc);
	HLSLByteAddressBuffer(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc,_U32 a_Index);
	virtual ~HLSLByteAddressBuffer();

	bool IsGpuWritable() const;

private:
	bool m_GpuWritable;
};


NAMESPACE_MENGINE_END