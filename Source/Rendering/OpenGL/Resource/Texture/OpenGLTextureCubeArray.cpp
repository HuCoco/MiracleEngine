#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureCubeArray.h>



Miracle::OpenGLTextureCubeArray::OpenGLTextureCubeArray(TextureCubeArray* a_Texture)
	: OpenGLTextureArray(a_Texture, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BINDING_CUBE_MAP_ARRAY)
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, m_Handle);

	const auto width = a_Texture->GetDimension(0);
	const auto height = a_Texture->GetDimension(1);
	const auto numItems = a_Texture->GetNumItems();
	const auto numCubes = a_Texture->GetNumCubes();
	glTexStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, m_NumLevels, m_InternalFormat, width, height, numItems);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_LEVEL, m_NumLevels - 1);

	if (a_Texture->GetData())
	{
		if (CanAutoGenerateMipmaps())
		{
			for (_U32 cube = 0; cube < numCubes; ++cube)
			{
				for (_U32 face = 0; face < a_Texture->CubeFaceCount; ++face)
				{
					auto data = a_Texture->GetDataBy(cube, face, 0);
					if (data)
					{
						auto item = a_Texture->GetItemIndex(cube, face);
						LoadTextureLevel(item, 0, data);
					}
				}
			}
			GenerateMipmaps();
		}
		else
		{
			for (_U32 cube = 0; cube < numCubes; ++cube)
			{
				for (_U32 face = 0; face < a_Texture->CubeFaceCount; ++face)
				{
					for (_U32 level = 0; level < m_NumLevels; ++level)
					{
						auto data = a_Texture->GetDataBy(cube, face, level);
						if (data)
						{
							auto item = a_Texture->GetItemIndex(cube, face);
							LoadTextureLevel(item, level, data);
						}
					}
				}
			}
		}
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);
}

Miracle::OpenGLTextureCubeArray::~OpenGLTextureCubeArray()
{
}

bool Miracle::OpenGLTextureCubeArray::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

void Miracle::OpenGLTextureCubeArray::LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data)
{
	auto texture = GetTexture();
	if (texture && a_Level < texture->GetNumLevels())
	{
		const auto width = texture->GetDimensionByLevel(a_Level, 0);
		const auto height = texture->GetDimensionByLevel(a_Level, 1);

		const auto cube = texture->GetCubeIndex(a_Level);
		const auto face = texture->GetFaceIndex(a_Level);

		GLenum targetFace = CubeFaceTarget[face];

		glTexSubImage3D(targetFace, a_Level, 0, 0, cube, width, height, 1,
			m_ExternalFormat, m_ExternalType, a_Data);
	}
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTextureCubeArray::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE_CUBE_ARRAY)
	{
		return std::make_shared<OpenGLTextureCubeArray>(static_cast<TextureCubeArray*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}