#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture3D.h>


Miracle::OpenGLTexture3D::OpenGLTexture3D(Texture3D* a_Texture)
	: OpenGLTextureSingle(a_Texture, GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D)
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_3D, m_Handle);

	const auto width = a_Texture->GetDimension(0);
	const auto height = a_Texture->GetDimension(1);
	const auto depth = a_Texture->GetDimension(2);
	glTexStorage3D(GL_TEXTURE_3D, m_NumLevels, m_InternalFormat, width, height, depth);

	Initialize();

	glBindTexture(GL_TEXTURE_3D, 0);
}

Miracle::OpenGLTexture3D::~OpenGLTexture3D()
{
}

bool Miracle::OpenGLTexture3D::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

void Miracle::OpenGLTexture3D::LoadTextureLevel(unsigned int a_Level, void* a_Data)
{
	auto texture = GetTexture();
	if (texture && a_Level < texture->GetNumLevels())
	{
		auto width = texture->GetDimensionByLevel(a_Level, 0);
		auto height = texture->GetDimensionByLevel(a_Level, 1);
		auto depth = texture->GetDimensionByLevel(a_Level, 2);

		glTexSubImage3D(GL_TEXTURE_3D, a_Level, 0, 0, 0, width, height, depth,
			m_ExternalFormat, m_ExternalType, a_Data);
	}
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTexture3D::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE3D)
	{
		return std::make_shared<OpenGLTexture3D>(static_cast<Texture3D*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
