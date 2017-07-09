#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN


class HLSLShaderVariable
{
public:
	struct Description
	{
		std::string Name;
		_U32 Offset;
		_U32 NumBytes;
		_U32 Flags;
		_U32 TextureStart;
		_U32 TextureNumSlots;
		_U32 SamplerStart;
		_U32 SamplerNumSlots;
		std::vector<unsigned char> DefaultValue;
	};

	HLSLShaderVariable();
	~HLSLShaderVariable();

	void SetDescription(const D3D11_SHADER_VARIABLE_DESC& desc);

	std::string const& GetName() const;
	_U32 GetOffset() const;
	_U32 GetNumBytes() const;
	_U32 GetFlags() const;
	_U32 GetTextureStart() const;
	_U32 GetTextureNumSlots() const;
	_U32 GetSamplerStart() const;
	_U32 GetSamplerNumSlots() const;
	std::vector<unsigned char> const& GetDefaultValue() const;
	
private:
	Description m_Desc;
};

NAMESPACE_MENGINE_END