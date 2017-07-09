#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/GraphicsResource.h>
#include <Rendering/Base/Resource/DataFormat.h>

NAMESPACE_MENGINE_BEGIN

class Texture : public GraphicsResource
{
protected:
	Texture(_U32 a_NumItems, DataFormat a_Format,_U32 a_NumDimensions,
		_U32 a_Dimensions1,_U32 a_Dimensions2,_U32 a_Dimensions3,
		bool a_HasMipmap,_U32 a_Type = GraphicsObject::TEXTURE);

public:
	~Texture();

	inline _U32 GetNumItems() const;
	inline DataFormat GetDataFormat() const;
	inline _U32 GetNumDimensions() const;
	inline _U32 GetDimension(int i) const;

	struct SubTextureResource
	{
		_U32 Item;
		_U32 Level;
		void* Data;
		_U32 RowPitch;
		_U32 SlicePitch;
	};

	enum { MAX_MIPMAP_LEVELS = 16 };

	inline bool HasMipmaps() const;
	inline _U32 GetNumLevels() const;
	inline _U32 GetDimensionByLevel(_U32 level, int dimension) const;
	inline _U32 GetNumElementsByLevel(_U32 level) const;
	inline _U32 GetNumBytesByLevel(_U32 level) const;
	inline _U32 GetOffsetByItemAndLevel(_U32 item, _U32 level) const;
	inline const void* GetDataByItemAndLevel(_U32 item, _U32 level) const;
	inline void* GetDataByItemAndLevel(_U32 item, _U32 level);

	inline _U32 GetNumSubresources() const;
	_U32 GetIndex(_U32 item, _U32 level) const;
	SubTextureResource GetSubresource(_U32 index) const;

	void AutogenerateMipmaps();
	inline bool WantAutogenerateMipmaps() const;
protected:

	static _U32 GetTotalElements(_U32 a_NumItems,
		_U32 a_Dimensions1, _U32 a_Dimensions2, _U32 a_Dimensions3,
		bool a_HasMipmap);

protected:
	_U32 m_NumItems;
	DataFormat m_Format;
	_U32 m_NumDimensions;
	_U32 m_NumLevels;
	std::array<std::array<_U32, 3>, MAX_MIPMAP_LEVELS> m_LevelDimension;
	std::array<_U32, MAX_MIPMAP_LEVELS> m_LevelNumBytes;
	std::vector<std::array<_U32, MAX_MIPMAP_LEVELS>> m_LevelOffset;
	bool m_HasMipmap;
	bool m_AutoGenerateMipmaps;
};


inline _U32 Texture::GetNumItems() const
{
	return m_NumItems;
}

inline DataFormat Texture::GetDataFormat() const
{
	return m_Format;
}

inline _U32 Texture::GetNumDimensions() const
{
	return m_NumDimensions;
}

inline _U32 Texture::GetDimension(int i) const
{
	return m_LevelDimension[0][i];
}

inline bool Texture::HasMipmaps() const
{
	return m_HasMipmap;
}

inline _U32 Texture::GetNumLevels() const
{
	return m_NumLevels;
}

inline _U32 Texture::GetDimensionByLevel(_U32 level, int dimension) const
{
	return m_LevelDimension[level][dimension];
}

inline _U32 Texture::GetNumElementsByLevel(_U32 level) const
{
	return m_LevelNumBytes[level] / m_ElementSize;
}

inline _U32 Texture::GetNumBytesByLevel(_U32 level) const
{
	return m_LevelNumBytes[level];
}

inline _U32 Texture::GetOffsetByItemAndLevel(_U32 item, _U32 level) const
{
	return m_LevelOffset[item][level];
}

inline const void* Texture::GetDataByItemAndLevel(_U32 item, _U32 level) const
{
	return m_pData ? ((char*)m_pData + m_LevelOffset[item][level]) : nullptr;
}

inline void* Texture::GetDataByItemAndLevel(_U32 item, _U32 level)
{
	return m_pData ? ((char*)m_pData + m_LevelOffset[item][level]) : nullptr;
}

inline _U32 Texture::GetNumSubresources() const
{
	return m_NumItems * m_NumLevels;
}

inline bool Texture::WantAutogenerateMipmaps() const
{
	return m_AutoGenerateMipmaps;
}


NAMESPACE_MENGINE_END