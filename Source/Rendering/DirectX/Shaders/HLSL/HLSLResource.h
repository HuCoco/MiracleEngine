#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
NAMESPACE_MENGINE_BEGIN

class HLSLResource
{
protected:
	HLSLResource(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_NumBytes);
	HLSLResource(const D3D11_SHADER_INPUT_BIND_DESC& desc, _U32 a_Index, _U32 a_NumBytes);
public:
	virtual ~HLSLResource();

	struct Description
	{
		std::string Name;
		D3D_SHADER_INPUT_TYPE Type;
		_U32 BindPoint;
		_U32 BindCount;
		_U32 Flags;
		D3D_RESOURCE_RETURN_TYPE ReturnType;
		D3D_SRV_DIMENSION Dimension;
		_U32 NumSamples;
	};

	const std::string& GetName() const;
	D3D_SHADER_INPUT_TYPE GetType() const;
	_U32 GetBindPoint() const;
	_U32 GetBindCount() const;
	_U32 GetFlags() const;
	D3D_RESOURCE_RETURN_TYPE GetReturnType() const;
	D3D_SRV_DIMENSION GetDimension() const;
	_U32 GetNumSamples() const;
	_U32 GetNumBytes() const;

private:
	Description m_Desc;
	_U32 m_NumBytes;
};

NAMESPACE_MENGINE_END