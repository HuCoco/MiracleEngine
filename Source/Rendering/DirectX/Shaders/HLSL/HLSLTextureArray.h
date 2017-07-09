#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLResource.h>

NAMESPACE_MENGINE_BEGIN


class HLSLTextureArray : public HLSLResource
{
public:
	HLSLTextureArray(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc);
	HLSLTextureArray(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index);
	~HLSLTextureArray();

	_U32 GetNumComponents() const;
	_U32 GetNumDimensions() const;
	bool IsGpuWritable() const;
private:
	void Initialize(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc);

	_U32 m_NumComponents;
	_U32 m_NumDimensions;
	bool m_GpuWritable;
};

NAMESPACE_MENGINE_END