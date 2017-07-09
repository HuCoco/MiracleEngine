#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/Texture.h>

NAMESPACE_MENGINE_BEGIN

class TextureArray : public Texture
{
protected:
	TextureArray(_U32 a_NumItems,DataFormat a_Format, _U32 a_NumDimensions,
		_U32 a_Dimension1, _U32 a_Dimension2, _U32 a_Dimension3, bool a_HasMipmap,
		_U32 a_Type = GraphicsObject::TEXTURE_ARRAY);
public:

	virtual ~TextureArray();
	inline _U32 GetOffsetByItemAndLevel(_U32 item, _U32 level) const;
	inline const void* GetDataByItemAndLevel(_U32 item, _U32 level) const;
	inline void* GetDataByItemAndLevel(_U32 item, _U32 level);

	//Cube Map
	static const _U32 CubeFacePositiveX = 0;
	static const _U32 CubeFaceNegativeX = 1;
	static const _U32 CubeFacePositiveY = 2;
	static const _U32 CubeFaceNegativeY = 3;
	static const _U32 CubeFacePositiveZ = 4;
	static const _U32 CubeFaceNegativeZ = 5;
	static const _U32 CubeFaceCount = 6;

	static const _I32 ShaderDataIndex = TextureArrayShaderDataIndex;
};

inline _U32 TextureArray::GetOffsetByItemAndLevel(_U32 item, _U32 level) const
{
	return Texture::GetOffsetByItemAndLevel(item, level);
}

inline const void* TextureArray::GetDataByItemAndLevel(_U32 item, _U32 level) const
{
	return Texture::GetDataByItemAndLevel(item, level);
}

inline void* TextureArray::GetDataByItemAndLevel(_U32 item, _U32 level)
{
	return Texture::GetDataByItemAndLevel(item, level);
}


NAMESPACE_MENGINE_END