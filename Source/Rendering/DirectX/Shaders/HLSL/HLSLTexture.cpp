#include "HLSLTexture.h"


Miracle::HLSLTexture::HLSLTexture(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index)
	: HLSLResource(a_Desc,a_Index,0)
{
	Initialize(a_Desc);
}

Miracle::HLSLTexture::HLSLTexture(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc)
	: HLSLResource(a_Desc,0)
{
	Initialize(a_Desc);
}

Miracle::HLSLTexture::~HLSLTexture()
{
}


void Miracle::HLSLTexture::Initialize(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc)
{
	m_NumComponents = ((a_Desc.uFlags >> 2) + 1);

	switch (a_Desc.Dimension)
	{
	case D3D_SRV_DIMENSION_TEXTURE1D:
		m_NumDimensions = 1;
		break;
	case D3D_SRV_DIMENSION_TEXTURE2D:
		m_NumDimensions = 2;
		break;
	case D3D_SRV_DIMENSION_TEXTURE3D:
		m_NumDimensions = 3;
		break;
	default:
		m_NumDimensions = 0;
		break;
	}

	m_GpuWritable = (a_Desc.Type == D3D_SIT_UAV_RWTYPED);
}


_U32 Miracle::HLSLTexture::GetNumComponents() const
{
	return m_NumComponents;
}

_U32 Miracle::HLSLTexture::GetNumDimensions() const
{	
	return m_NumDimensions;
}

bool Miracle::HLSLTexture::IsGpuWritable() const
{
	return m_GpuWritable;
}
