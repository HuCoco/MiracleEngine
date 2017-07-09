#include <Rendering/Base/Resource/Texture/Texture.h>
#include <Core/Mathematics/MathUtils.h>


Miracle::Texture::Texture(_U32 a_NumItems, DataFormat a_Format, _U32 a_NumDimensions,
	_U32 a_Dimensions1, _U32 a_Dimensions2, _U32 a_Dimensions3, bool a_HasMipmap, _U32 a_Type /*= GraphicsObject::TEXTURE*/)
	: GraphicsResource(GetTotalElements(a_NumItems,a_Dimensions1,a_Dimensions2,a_Dimensions3,a_HasMipmap),DataFormatUtils::GetDataFormatBytes(a_Format),a_Type)
	, m_NumItems(a_NumItems)
	, m_Format(a_Format)
	, m_NumDimensions(a_NumDimensions)
	, m_NumLevels(1)
	, m_LevelOffset(a_NumItems)
	, m_HasMipmap(a_HasMipmap)
	, m_AutoGenerateMipmaps(false)
{
	if (m_NumDimensions < 1 || m_NumDimensions > 3)
	{
		MENGINE_ASSERT_MSG(false,"Invalid number of dimensions.");
		m_NumDimensions = 1;
	}

	for (_U32 level = 0; level < MAX_MIPMAP_LEVELS; ++level)
	{
		m_LevelDimension[level][0] = 0;
		m_LevelDimension[level][1] = 0;
		m_LevelDimension[level][2] = 0;
		m_LevelNumBytes[level] = 0;
	}

	for (_U32 item = 0; item < m_NumItems; ++item)
	{
		for (_U32 level = 0; level < MAX_MIPMAP_LEVELS; ++level)
		{
			m_LevelOffset[item][level] = 0;
		}
	}

	m_LevelDimension[0][0] = a_Dimensions1;
	m_LevelDimension[0][1] = a_Dimensions2;
	m_LevelDimension[0][2] = a_Dimensions3;
	m_LevelNumBytes[0] = a_Dimensions1 * a_Dimensions2 * a_Dimensions3 * m_ElementSize;

	if (m_HasMipmap)
	{
		_U32 Dim1Power = MathUtils::Log2(MathUtils::RoundDownToPowerOfTwo(a_Dimensions1));
		_U32 Dim2Power = MathUtils::Log2(MathUtils::RoundDownToPowerOfTwo(a_Dimensions2));
		_U32 Dim3Power = MathUtils::Log2(MathUtils::RoundDownToPowerOfTwo(a_Dimensions3));
		_U32 numLevels = MENGINE_MAX(Dim1Power, MENGINE_MAX(Dim2Power, Dim3Power)) + 1;

		for (_U32 level = 1; level < numLevels; ++level)
		{
			if (a_Dimensions1 > 1) { a_Dimensions1 >>= 1; }
			if (a_Dimensions2 > 1) { a_Dimensions2 >>= 1; }
			if (a_Dimensions3 > 1) { a_Dimensions3 >>= 1; }

			m_LevelNumBytes[level] = a_Dimensions1 * a_Dimensions2 * a_Dimensions3 * m_ElementSize;
			m_LevelDimension[level][0] = a_Dimensions1;
			m_LevelDimension[level][1] = a_Dimensions2;
			m_LevelDimension[level][2] = a_Dimensions3;
		}

		_U32 numBytes = 0;
		for (_U32 item = 0; item < m_NumItems; ++item)
		{
			for (_U32 level = 0; level < m_NumLevels; ++level)
			{
				m_LevelOffset[item][level] = numBytes;
				numBytes += m_LevelNumBytes[level];
			}
		}
	}
	else
	{
		for (_U32 item = 1; item < m_NumItems; ++item)
		{
			m_LevelOffset[item][0] = item * m_LevelNumBytes[0];
		}
	}
}

Miracle::Texture::~Texture()
{
}

_U32 Miracle::Texture::GetTotalElements(_U32 a_NumItems, _U32 a_Dimensions1, _U32 a_Dimensions2, _U32 a_Dimensions3, bool a_HasMipmap)
{
	_U32 numElementPerItem = a_Dimensions1 * a_Dimensions2 * a_Dimensions3;
	if (a_HasMipmap)
	{
		_U32 Dim1Power = MathUtils::Log2(MathUtils::RoundDownToPowerOfTwo(a_Dimensions1));
		_U32 Dim2Power = MathUtils::Log2(MathUtils::RoundDownToPowerOfTwo(a_Dimensions2));
		_U32 Dim3Power = MathUtils::Log2(MathUtils::RoundDownToPowerOfTwo(a_Dimensions3));
		_U32 numLevels = MENGINE_MAX(Dim1Power,MENGINE_MAX(Dim2Power, Dim3Power)) + 1;
		for (_U32 level = 1; level < numLevels; ++level)
		{
			if (a_Dimensions1 > 1) { a_Dimensions1 >>= 1; }
			if (a_Dimensions2 > 1) { a_Dimensions2 >>= 1; }
			if (a_Dimensions3 > 1) { a_Dimensions3 >>= 1; }

			numElementPerItem += a_Dimensions1 * a_Dimensions2 * a_Dimensions3;
		}
	}
	return a_NumItems*numElementPerItem;
}

_U32 Miracle::Texture::GetIndex(_U32 item, _U32 level) const
{
	if (item < m_NumItems && level < m_NumLevels)
	{
		return m_NumLevels * item + level;
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Invalid input.");
		return 0;
	}
}

// TODO: Maybe this API is uncomfortable to use
Miracle::Texture::SubTextureResource Miracle::Texture::GetSubresource(_U32 index) const
{
	SubTextureResource sr;
	if (index < GetNumSubresources())
	{
		sr.Item = index / m_NumLevels;
		sr.Level = index % m_NumLevels;
		sr.Data = const_cast<void*>(GetDataByItemAndLevel(sr.Item, sr.Level));
		sr.RowPitch = m_LevelDimension[sr.Level][0] * m_ElementSize;
		sr.SlicePitch = m_LevelDimension[sr.Level][1] * sr.RowPitch;
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Invalid input.");
		sr.Item = 0;
		sr.Level = 0;
		sr.Data = nullptr;
		sr.RowPitch = 0;
		sr.SlicePitch = 0;
	}
	return sr;
}

void Miracle::Texture::AutogenerateMipmaps()
{
	if (m_HasMipmap)
	{
		m_AutoGenerateMipmaps = true;
	}
}
