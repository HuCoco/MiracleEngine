#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureCube.h>


Miracle::OpenGLTextureCube::OpenGLTextureCube(TextureCube* a_Texture)
	: OpenGLTextureArray(a_Texture, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BINDING_CUBE_MAP)
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Handle);

	const auto width = a_Texture->GetDimension(0);
	const auto height = a_Texture->GetDimension(1);
	glTexStorage2D(GL_TEXTURE_CUBE_MAP, m_NumLevels, m_InternalFormat, width, height);

	Initialize();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Miracle::OpenGLTextureCube::~OpenGLTextureCube()
{
}

void Miracle::OpenGLTextureCube::LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data)
{
	auto texture = GetTexture();
	if (texture && a_Level < texture->GetNumLevels())
	{
		const auto width = texture->GetDimension(0);
		const auto height = texture->GetDimension(1);

		GLenum targetFace = CubeFaceTarget[a_Item];

		glTexSubImage2D(targetFace, a_Level, 0, 0, width, height,
			m_ExternalFormat, m_ExternalType, a_Data);
	}
}

bool Miracle::OpenGLTextureCube::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTextureCube::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE_CUBE)
	{
		return std::make_shared<OpenGLTextureCube>(static_cast<TextureCube*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
