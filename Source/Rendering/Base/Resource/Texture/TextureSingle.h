#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/Texture.h>

NAMESPACE_MENGINE_BEGIN

class TextureSingle : public Texture
{
protected:
	TextureSingle(DataFormat a_Format, _U32 a_NumDimensions, _U32 a_Dimension1, _U32 a_Dimension2, _U32 a_Dimension3, bool a_HasMipmap,
		_U32 a_Type = GraphicsObject::TEXTURE_SINGLE);

public:
	virtual ~TextureSingle();
	inline _U32 GetOffsetByLevel(_U32 level) const;
	inline const void* GetDataByLevel(_U32 level) const;
	inline void* GetDataByLevel(_U32 level);

public:
	static const _I32 ShaderDataIndex = TextureSingleShaderDataIndex;
};

inline _U32 TextureSingle::GetOffsetByLevel(_U32 level) const 
{
	return Texture::GetOffsetByItemAndLevel(0, level);
}

inline const void* TextureSingle::GetDataByLevel(_U32 level) const
{
	return Texture::GetDataByItemAndLevel(0, level);
}

inline void* TextureSingle::GetDataByLevel(_U32 level)
{
	return Texture::GetDataByItemAndLevel(0, level);
}

NAMESPACE_MENGINE_END