#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>

NAMESPACE_MENGINE_BEGIN

class TextureCubeArray : public TextureArray
{
public:
	TextureCubeArray(_U32 a_NumCubes,DataFormat a_Format,_U32 a_Length, bool a_HasMipmap);
	~TextureCubeArray();

	_U32 GetNumCubes() const;
	_U32 GetLength() const;

	inline _U32 GetItemIndex(_U32 a_CubeIndex, _U32 a_FaceIndex) const;
	inline _U32 GetCubeIndex(_U32 a_ItemIndex) const;
	inline _U32 GetFaceIndex(_U32 a_ItemIndex) const;

	inline _U32 GetOffset(_U32 cube, _U32 face, _U32 level) const;
	inline const void* GetDataBy(_U32 cube, _U32 face, _U32 level) const;
	inline void* GetDataBy(_U32 cube, _U32 face, _U32 level);

	inline _U32 GetIndex(_U32 cube, _U32 face, _U32 level) const;

private:
	_U32 m_NumCubes;
};

inline _U32 TextureCubeArray::GetItemIndex(_U32 a_CubeIndex, _U32 a_FaceIndex) const
{
	return a_CubeIndex * 6 + a_FaceIndex;
}

inline _U32 TextureCubeArray::GetCubeIndex(_U32 a_ItemIndex) const
{
	return a_ItemIndex / TextureArray::CubeFaceCount;
}

inline _U32 TextureCubeArray::GetFaceIndex(_U32 a_ItemIndex) const
{
	return a_ItemIndex % TextureArray::CubeFaceCount;
}

inline _U32 TextureCubeArray::GetOffset(_U32 a_CubeIndex, _U32 a_FaceIndex, _U32 a_Level) const
{
	return TextureArray::GetOffsetByItemAndLevel(GetItemIndex(a_CubeIndex, a_FaceIndex), a_Level);
}

inline const void* TextureCubeArray::GetDataBy(_U32 a_CubeIndex, _U32 a_FaceIndex, _U32 a_Level) const
{
	return TextureArray::GetDataByItemAndLevel(GetItemIndex(a_CubeIndex, a_FaceIndex), a_Level);
}

inline void*TextureCubeArray::GetDataBy(_U32 a_CubeIndex, _U32 a_FaceIndex, _U32 a_Level)
{
	return TextureArray::GetDataByItemAndLevel(GetItemIndex(a_CubeIndex, a_FaceIndex), a_Level);
}

inline _U32 TextureCubeArray::GetIndex(_U32 a_CubeIndex, _U32 a_FaceIndex, _U32 a_Level) const
{
	return m_NumLevels * (a_CubeIndex * TextureArray::CubeFaceCount + a_FaceIndex) + a_Level;
}

NAMESPACE_MENGINE_END