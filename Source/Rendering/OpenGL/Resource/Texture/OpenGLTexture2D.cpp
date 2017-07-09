#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture2D.h>


Miracle::OpenGLTexture2D::OpenGLTexture2D(Texture2D* a_Texture)
	: OpenGLTextureSingle(a_Texture, GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D)
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_2D, m_Handle);

	const auto width = a_Texture->GetDimension(0);
	const auto height = a_Texture->GetDimension(1);
	glTexStorage2D(GL_TEXTURE_2D, m_NumLevels, m_InternalFormat, width, height);

	Initialize();

	glBindTexture(GL_TEXTURE_2D, 0);
}

Miracle::OpenGLTexture2D::~OpenGLTexture2D()
{

}

bool Miracle::OpenGLTexture2D::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexure();

	return texture &&
		texture->HasMipmaps() &&
		texture->WantAutogenerateMipmaps() &&
		!texture->IsShared();
}

void Miracle::OpenGLTexture2D::LoadTextureLevel(unsigned int a_Level, void* a_Data)
{
	auto texture = GetTexture();
	if (texture && a_Level < texture->GetNumLevels())
	{
		auto width = texture->GetDimension(0);
		auto height = texture->GetDimension(1);

		glTexSubImage2D(GL_TEXTURE_2D, a_Level, 0, 0, width, height,
			m_ExternalFormat, m_ExternalType, a_Data);
	}
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTexture2D::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE2D)
	{
		return std::make_shared<OpenGLTexture2D>(static_cast<Texture2D*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

