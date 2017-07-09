#include "HLSLTextureArray.h"



Miracle::HLSLTextureArray::HLSLTextureArray(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc)
	: HLSLResource(a_Desc,0)
{
	Initialize(a_Desc);
}

Miracle::HLSLTextureArray::HLSLTextureArray(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index)
	: HLSLResource(a_Desc,a_Index,0)
{
	Initialize(a_Desc);
}

void Miracle::HLSLTextureArray::Initialize(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc)
{
	m_NumComponents = ((a_Desc.uFlags >> 2) + 1);

	switch (a_Desc.Dimension)
	{
	case D3D_SRV_DIMENSION_TEXTURE1DARRAY:
		m_NumDimensions = 1;
		break;
	case D3D_SRV_DIMENSION_TEXTURE2DARRAY:
	case D3D_SRV_DIMENSION_TEXTURE2DMSARRAY:
	case D3D_SRV_DIMENSION_TEXTURECUBE:
	case D3D_SRV_DIMENSION_TEXTURECUBEARRAY:
		m_NumDimensions = 2;
		break;
	default:
		m_NumDimensions = 0;
		break;
	}

	m_GpuWritable = (a_Desc.Type == D3D_SIT_UAV_RWTYPED);
}

Miracle::HLSLTextureArray::~HLSLTextureArray()
{
}

_U32 Miracle::HLSLTextureArray::GetNumComponents() const
{
	return m_NumComponents;
}

_U32 Miracle::HLSLTextureArray::GetNumDimensions() const
{
	return m_NumDimensions;
}

bool Miracle::HLSLTextureArray::IsGpuWritable() const
{
	return m_GpuWritable;
}


