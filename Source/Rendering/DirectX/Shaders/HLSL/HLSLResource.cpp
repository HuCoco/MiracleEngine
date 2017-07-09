#include <Rendering/DirectX/Shaders/HLSL/HLSLResource.h>



Miracle::HLSLResource::HLSLResource(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_NumBytes)
	: m_NumBytes(a_NumBytes)
{
	m_Desc.Name = std::string(a_Desc.Name);
	m_Desc.BindPoint = a_Desc.BindPoint;
	m_Desc.BindCount = a_Desc.BindCount;
	m_Desc.Type = a_Desc.Type;
	m_Desc.Flags = a_Desc.uFlags;
	m_Desc.ReturnType = a_Desc.ReturnType;
	m_Desc.Dimension = a_Desc.Dimension;
	m_Desc.NumSamples = a_Desc.NumSamples;
}

Miracle::HLSLResource::HLSLResource(const D3D11_SHADER_INPUT_BIND_DESC& desc, _U32 a_Index, _U32 a_NumBytes)
	: m_NumBytes(a_NumBytes)
{
	m_Desc.Name = std::string(desc.Name) + "[" + std::to_string(a_Index) + "]";
	m_Desc.BindPoint = desc.BindPoint + a_Index;
	m_Desc.BindCount = 1;
	m_Desc.Type = desc.Type;
	m_Desc.Flags = desc.uFlags;
	m_Desc.ReturnType = desc.ReturnType;
	m_Desc.Dimension = desc.Dimension;
	m_Desc.NumSamples = desc.NumSamples;
}

Miracle::HLSLResource::~HLSLResource()
{
}

const std::string& Miracle::HLSLResource::GetName() const
{
	return m_Desc.Name;
}

D3D_SHADER_INPUT_TYPE Miracle::HLSLResource::GetType() const
{
	return m_Desc.Type;
}

_U32 Miracle::HLSLResource::GetBindPoint() const
{
	return m_Desc.BindPoint;
}

_U32 Miracle::HLSLResource::GetBindCount() const
{
	return m_Desc.BindCount;
}

_U32 Miracle::HLSLResource::GetFlags() const
{
	return m_Desc.Flags;
}

D3D_RESOURCE_RETURN_TYPE Miracle::HLSLResource::GetReturnType() const
{
	return m_Desc.ReturnType;
}

D3D_SRV_DIMENSION Miracle::HLSLResource::GetDimension() const
{
	return m_Desc.Dimension;
}

_U32 Miracle::HLSLResource::GetNumSamples() const
{
	return m_Desc.NumSamples;
}

_U32 Miracle::HLSLResource::GetNumBytes() const
{
	return m_NumBytes;
}
