#include "HLSLShaderVariable.h"



Miracle::HLSLShaderVariable::HLSLShaderVariable()
{
}


Miracle::HLSLShaderVariable::~HLSLShaderVariable()
{
}

void Miracle::HLSLShaderVariable::SetDescription(const D3D11_SHADER_VARIABLE_DESC& a_Desc)
{
	m_Desc.Name = std::string(a_Desc.Name ? a_Desc.Name : "");
	m_Desc.Offset = a_Desc.StartOffset;
	m_Desc.NumBytes = a_Desc.Size;
	m_Desc.Flags = a_Desc.uFlags;
	m_Desc.TextureStart = a_Desc.StartTexture;
	m_Desc.TextureNumSlots = a_Desc.TextureSize;
	m_Desc.SamplerStart = a_Desc.StartSampler;
	m_Desc.SamplerNumSlots = a_Desc.SamplerSize;
	if (a_Desc.DefaultValue && a_Desc.Size > 0)
	{
		m_Desc.DefaultValue.resize(a_Desc.Size);
		memcpy(&m_Desc.DefaultValue[0], a_Desc.DefaultValue, a_Desc.Size);
	}
}

std::string const& Miracle::HLSLShaderVariable::GetName() const
{
	return m_Desc.Name;
}

_U32 Miracle::HLSLShaderVariable::GetOffset() const
{
	return m_Desc.Offset;
}

_U32 Miracle::HLSLShaderVariable::GetNumBytes() const
{
	return m_Desc.NumBytes;
}

_U32 Miracle::HLSLShaderVariable::GetFlags() const
{
	return m_Desc.Flags;
}

_U32 Miracle::HLSLShaderVariable::GetTextureStart() const
{
	return m_Desc.TextureStart;
}

_U32 Miracle::HLSLShaderVariable::GetTextureNumSlots() const
{
	return m_Desc.TextureNumSlots;
}

_U32 Miracle::HLSLShaderVariable::GetSamplerStart() const
{
	return m_Desc.SamplerStart;
}

_U32 Miracle::HLSLShaderVariable::GetSamplerNumSlots() const
{
	return m_Desc.SamplerNumSlots;
}

std::vector<unsigned char> const& Miracle::HLSLShaderVariable::GetDefaultValue() const
{
	return m_Desc.DefaultValue;
}
