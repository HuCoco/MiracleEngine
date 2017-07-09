#include "OpenGLTextureSingle.h"

Miracle::OpenGLTextureSingle::OpenGLTextureSingle(TextureSingle* a_Texture, GLenum a_Target, GLenum a_TargetBinding)
	: OpenGLTexture(a_Texture,a_Target,a_TargetBinding)
{
	std::fill(std::begin(m_LevelPixelUnpackBuffer), std::end(m_LevelPixelUnpackBuffer), 0);
	std::fill(std::begin(m_LevelPixelPackBuffer), std::end(m_LevelPixelPackBuffer), 0);
}

Miracle::OpenGLTextureSingle::~OpenGLTextureSingle()
{
	for (_U32 level = 0; level < m_NumLevels; ++level)
	{
		glDeleteBuffers(1, &m_LevelPixelUnpackBuffer[level]);
		glDeleteBuffers(1, &m_LevelPixelPackBuffer[level]);
	}
}

void Miracle::OpenGLTextureSingle::Initialize()
{
	GLint prevBinding;
	glGetIntegerv(m_TargetBinding, &prevBinding);
	glBindTexture(m_Target, m_Handle);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	glTexParameteri(m_Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(m_Target, GL_TEXTURE_MAX_LEVEL, m_NumLevels - 1);

	auto texture = GetTexture();
	if (texture->GetData())
	{
		if (CanAutoGenerateMipmaps())
		{
			auto data = texture->GetDataByLevel(0);
			if (data)
			{
				LoadTextureLevel(0, data);
				GenerateMipmaps();
			}
		}
		else
		{
			for (_U32 level = 0; level < m_NumLevels; ++level)
			{
				auto data = texture->GetDataByLevel(level);
				if (data)
				{
					LoadTextureLevel(level, data);
				}
			}
		}
	}
	glBindTexture(m_Target, prevBinding);
}

bool Miracle::OpenGLTextureSingle::Update()
{
	auto texture = GetTexture();
	
	if (CanAutoGenerateMipmaps())
	{
		if (!Update(0))
		{
			return false;
		}
		GenerateMipmaps();
	}
	else
	{
		const auto numLevels = texture->GetNumLevels();
		for (_U32 level = 0; level < numLevels; ++level)
		{
			if (!Update(level))
			{
				return false;
			}
		}
	}
	return true;
}

bool Miracle::OpenGLTextureSingle::Update(_U32 a_Level)
{
	auto texture = GetTexture();
	if (texture->GetUsage() != GraphicsResource::Usage::DYNAMIC)
	{
		MENGINE_ASSERT_MSG(false, "Texture usage is not DYNAMIC.");
		return false;
	}

	if (CanAutoGenerateMipmaps() && a_Level > 0)
	{
		MENGINE_ASSERT_MSG(false,"Cannot update automatically generated mipmaps in GPU");
		return false;
	}

	auto const numLevels = texture->GetNumLevels();
	if (a_Level >= numLevels)
	{
		MENGINE_ASSERT_MSG(false,"Level for Texture is out of range");
		return false;
	}

	auto data = texture->GetDataByLevel(a_Level);
	auto numBytes = texture->GetNumBytesByLevel(a_Level);
	if ((nullptr == data) || (0 == numBytes))
	{
		MENGINE_ASSERT_MSG(false,"No source data for Texture.");
		return false;
	}

	auto const target = GetTarget();
	glBindTexture(target, m_Handle);

	auto pixBuffer = m_LevelPixelUnpackBuffer[a_Level];
	if (0 != pixBuffer)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixBuffer);
		glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, numBytes, data);
		LoadTextureLevel(a_Level, 0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
	else
	{
		LoadTextureLevel(a_Level, data);
	}

	glBindTexture(target, 0);

	return true;
}

bool Miracle::OpenGLTextureSingle::GenerateMipmaps()
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

bool Miracle::OpenGLTextureSingle::CopyGraphMem2Mem()
{
	auto texture = GetTexture();
	const auto numLevels = texture->GetNumLevels();
	for (_U32 level = 0; level < numLevels; ++level)
	{
		if (!CopyGraphMem2Mem(level))
		{
			return false;
		}
	}

	return true;
}

bool Miracle::OpenGLTextureSingle::CopyGraphMem2Mem(_U32 level)
{
	if (!PreparedForCopy(GL_READ_ONLY))
	{
		return false;
	}

	auto texture = GetTexture();

	auto const numLevels = texture->GetNumLevels();
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

	auto data = texture->GetDataByLevel(level);
	auto numBytes = texture->GetNumBytesByLevel(level);
	if ((nullptr == data) || (0 == numBytes))
	{
		MENGINE_ASSERT_MSG(false,"No target data for Texture level=" + level);
		return false;
	}

	auto const target = GetTarget();
	glBindTexture(target, m_Handle);

	glBindBuffer(GL_PIXEL_PACK_BUFFER, pixBuffer);
	glGetTexImage(target, level, m_ExternalFormat, m_ExternalType, 0);
	glGetBufferSubData(GL_PIXEL_PACK_BUFFER, 0, numBytes, data);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	glBindTexture(target, 0);

	return true;
}

bool Miracle::OpenGLTextureSingle::CopyMem2GraphMem()
{
	auto texture = GetTexture();
	auto const numLevels = texture->GetNumLevels();
	for (unsigned int level = 0; level < numLevels; ++level)
	{
		if (!CopyMem2GraphMem(level))
		{
			return false;
		}
	}

	return true;
}

bool Miracle::OpenGLTextureSingle::CopyMem2GraphMem(_U32 level)
{
	if (!PreparedForCopy(GL_WRITE_ONLY))
	{
		return false;
	}

	return DoCopyMem2GraphMem(level);
}

bool Miracle::OpenGLTextureSingle::DoCopyMem2GraphMem(unsigned int level)
{
	auto texture = GetTexture();

	if (CanAutoGenerateMipmaps() && (level > 0))
	{
		MENGINE_ASSERT_MSG(false,"Cannot update automatically generated mipmaps in GPU");
		return false;
	}

	auto const numLevels = texture->GetNumLevels();
	if (level >= numLevels)
	{
		MENGINE_ASSERT_MSG(false,"Level for Texture is out of range");
		return false;
	}

	auto data = texture->GetDataByLevel(level);
	auto numBytes = texture->GetNumBytesByLevel(level);
	if ((nullptr == data) || (0 == numBytes))
	{
		MENGINE_ASSERT_MSG(false,"No source data for Texture level=" + level);
		return false;
	}

	auto const target = GetTarget();
	glBindTexture(target, m_Handle);

	auto pixBuffer = m_LevelPixelUnpackBuffer[level];
	if (0 != pixBuffer)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixBuffer);
		glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, numBytes, data);
		LoadTextureLevel(level, 0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
	else
	{
		LoadTextureLevel(level, data);
	}

	glBindTexture(target, 0);

	return true;

}
