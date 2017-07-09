#include "OpenGLTextureArray.h"

const GLenum Miracle::OpenGLTextureArray::CubeFaceTarget[6] =
{
	GL_TEXTURE_CUBE_MAP_POSITIVE_X, // CubeFacePositiveX
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X, // CubeFaceNegativeX
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y, // CubeFacePositiveY
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, // CubeFaceNegativeY
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z, // CubeFacePositiveZ
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z  // CubeFaceNegativeZ
};

Miracle::OpenGLTextureArray::OpenGLTextureArray(TextureArray* a_Texture, GLenum a_Target, GLenum a_TargetBinding)
	: OpenGLTexture(a_Texture,a_Target,a_TargetBinding)
{
	std::fill(std::begin(m_LevelPixelUnpackBuffer), std::end(m_LevelPixelUnpackBuffer), 0);
	std::fill(std::begin(m_LevelPixelPackBuffer), std::end(m_LevelPixelPackBuffer), 0);
}

Miracle::OpenGLTextureArray::~OpenGLTextureArray()
{
	for (_U32 level = 0; level < m_NumLevels; ++level)
	{
		glDeleteBuffers(1, &m_LevelPixelUnpackBuffer[level]);
		glDeleteBuffers(1, &m_LevelPixelPackBuffer[level]);
	}
}

void Miracle::OpenGLTextureArray::Initialize()
{
	GLint prevBinding;
	glGetIntegerv(m_TargetBinding, &prevBinding);
	glBindTexture(m_Target, m_Handle);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	glTexParameteri(m_Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(m_Target, GL_TEXTURE_MAX_LEVEL, m_NumLevels - 1);

	auto texture = GetTexture();
	const auto numItems = texture->GetNumItems();
	if (texture->GetData())
	{
		if (CanAutoGenerateMipmaps())
		{
			for (_U32 item = 0; item < numItems; ++item)
			{
				auto data = texture->GetDataByItemAndLevel(item, 0);
				if (data)
				{
					LoadTextureLevel(item, 0, data);
				}
			}
			GenerateMipmaps();
		}
		else
		{
			for (_U32 item = 0; item < numItems; ++item)
			{
				for (_U32 level = 0; level < m_NumLevels; ++level)
				{
					auto data = texture->GetDataByItemAndLevel(item, level);
					if (data)
					{
						LoadTextureLevel(item, level, data);
					}
				}
			}
		}
	}

	glBindTexture(m_Target, prevBinding);
}


bool Miracle::OpenGLTextureArray::Update()
{
	auto texture = GetTexture();
	const auto numItems = texture->GetNumItems();

	if (CanAutoGenerateMipmaps())
	{
		for (_U32 item = 0; item < numItems; ++item)
		{
			if (!Update(item, 0))
			{
				return false;
			}
		}
		GenerateMipmaps();
	}
	else
	{
		const auto numLevels = texture->GetNumLevels();
		for (_U32 item = 0; item < numItems; ++item)
		{
			for (_U32 level = 0; level < numLevels; ++level)
			{
				if (!Update(item, level))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Miracle::OpenGLTextureArray::Update(_U32 a_Item, _U32 a_Level)
{
	auto texture = GetTexture();
	if (texture->GetUsage() != GraphicsResource::Usage::DYNAMIC)
	{
		MENGINE_ASSERT_MSG(false,"Texture usage is not DYNAMIC.");
		return false;
	}

	if (CanAutoGenerateMipmaps() && (a_Level > 0))
	{
		MENGINE_ASSERT_MSG(false, "Cannot update automatically generated mipmaps in GPU");
		return false;
	}

	const auto numItems = texture->GetNumItems();
	if (a_Item >= numItems)
	{
		MENGINE_ASSERT_MSG(false, "Item for TextureArray is out of range");
		return false;
	}

	const auto numLevels = texture->GetNumLevels();
	if (a_Level >= numLevels)
	{
		MENGINE_ASSERT_MSG(false, "Level for TextureArray is out of range");
		return false;
	}

	auto data = texture->GetDataByItemAndLevel(a_Item, a_Level);
	auto numBytes = texture->GetNumBytesByLevel(a_Level);
	if ((nullptr == data) || (0 == numBytes))
	{
		MENGINE_ASSERT_MSG(false, "No source data for TextureArra.");
		return false;
	}

	const auto target = GetTarget();
	glBindTexture(target, m_Handle);

	auto pixBuffer = m_LevelPixelUnpackBuffer[a_Level];
	if (0 != pixBuffer)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixBuffer);
		glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, numBytes, data);
		LoadTextureLevel(a_Item, a_Level, 0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
	else
	{
		LoadTextureLevel(a_Item, a_Level, data);
	}

	glBindTexture(target, 0);

	return true;
}

bool Miracle::OpenGLTextureArray::GenerateMipmaps()
{
	if (CanAutoGenerateMipmaps())
	{
		GLint prevBinding;
		glGetIntegerv(m_TargetBinding, &prevBinding);
		glBindTexture(m_Target, m_Handle);

		glGenerateMipmap(m_Target);

		glBindTexture(m_Target, prevBinding);

		return true;
	}
	return false;
}

bool Miracle::OpenGLTextureArray::CopyMem2GraphMem()
{
	auto texture = GetTexture();
	const auto numItems = texture->GetNumItems();

	if (CanAutoGenerateMipmaps())
	{
		for (_U32 item = 0; item < numItems; ++item)
		{
			if (!CopyMem2GraphMem(item, 0))
			{
				return false;
			}
		}
		GenerateMipmaps();
	}
	else
	{
		const auto numLevels = texture->GetNumLevels();
		for (_U32 item = 0; item < numItems; ++item)
		{
			for (_U32 level = 0; level < numLevels; ++level)
			{
				if (!CopyMem2GraphMem(item, level))
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Miracle::OpenGLTextureArray::CopyMem2GraphMem(_U32 item, _U32 level)
{
	if (!PreparedForCopy(GL_WRITE_ONLY))
	{
		return false;
	}

	return DoCopyMem2GraphMem(item, level);
}

bool Miracle::OpenGLTextureArray::CopyGraphMem2Mem()
{
	auto texture = GetTexture();
	const auto numItems = texture->GetNumItems();
	const auto numLevels = texture->GetNumLevels();
	for (_U32 item = 0; item < numItems; ++item)
	{
		for (_U32 level = 0; level < numLevels; ++level)
		{
			if (!CopyGraphMem2Mem(item, level))
			{
				return false;
			}
		}
	}

	return true;
}

bool Miracle::OpenGLTextureArray::CopyGraphMem2Mem(_U32 item, _U32 level)
{
	if (!PreparedForCopy(GL_READ_ONLY))
	{
		return false;
	}

	auto texture = GetTexture();

	const auto numItems = texture->GetNumItems();
	if (item >= numItems)
	{
		MENGINE_ASSERT_MSG(false,"Item for Texture is out of range");
		return false;
	}

	const auto numLevels = texture->GetNumLevels();
	if (level >= numLevels)
	{
		MENGINE_ASSERT_MSG(false,"Level for Texture is out of range");
		return false;
	}

	auto pixBuffer = m_LevelPixelPackBuffer[level];
	if (0 == pixBuffer)
	{
		MENGINE_ASSERT_MSG(false,"Staging buffer not defined for level=" + level);
		return false;
	}

	auto data = texture->GetDataByItemAndLevel(item, level);
	auto numBytes = texture->GetNumBytesByLevel(level);
	if ((nullptr == data) || (0 == numBytes))
	{
		MENGINE_ASSERT_MSG(false,"No target data for Texture level=" + level);
		return false;
	}

	const auto target = GetTarget();
	glBindTexture(target, m_Handle);

	glBindBuffer(GL_PIXEL_PACK_BUFFER, pixBuffer);
	glGetTexImage(target, level, m_ExternalFormat, m_ExternalType, 0);
	glGetBufferSubData(GL_PIXEL_PACK_BUFFER, 0, numBytes, data);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	glBindTexture(target, 0);

	return true;
}

bool Miracle::OpenGLTextureArray::DoCopyMem2GraphMem(_U32 item, _U32 level)
{
	auto texture = GetTexture();

	if (CanAutoGenerateMipmaps() && (level > 0))
	{
		MENGINE_ASSERT_MSG(false,"Cannot update automatically generated mipmaps in GPU");
		return false;
	}

	const auto numItems = texture->GetNumItems();
	if (item >= numItems)
	{
		MENGINE_ASSERT_MSG(false,"Item for TextureArray is out of range");
		return false;
	}

	const auto numLevels = texture->GetNumLevels();
	if (level >= numLevels)
	{
		MENGINE_ASSERT_MSG(false,"Level for TextureArray is out of range");
		return false;
	}

	auto data = texture->GetDataByItemAndLevel(item, level);
	auto numBytes = texture->GetNumBytesByLevel(level);
	if ((nullptr == data) || (0 == numBytes))
	{
		MENGINE_ASSERT_MSG(false,"No source data for TextureArray level=" + level);
		return false;
	}

	const auto target = GetTarget();
	glBindTexture(target, m_Handle);

	auto pixBuffer = m_LevelPixelUnpackBuffer[level];
	if (0 != pixBuffer)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixBuffer);
		glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, numBytes, data);
		LoadTextureLevel(item, level, 0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
	else
	{
		LoadTextureLevel(item, level, data);
	}

	glBindTexture(target, 0);

	return true;
}

