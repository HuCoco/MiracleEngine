#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture1D.h>

Miracle::OpenGLTexture1D::OpenGLTexture1D(Texture1D* a_Texture)
	: OpenGLTextureSingle(a_Texture, GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D)
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_1D, m_Handle);

	const auto length = a_Texture->GetDimension(0);
	glTexStorage1D(GL_TEXTURE_1D, m_NumLevels, m_InternalFormat, length);

	Initialize();

	glBindTexture(GL_TEXTURE_1D, 0);

}

Miracle::OpenGLTexture1D::~OpenGLTexture1D()
{

}

bool Miracle::OpenGLTexture1D::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

void Miracle::OpenGLTexture1D::LoadTextureLevel(unsigned int a_Level, void* a_Data)
{
	auto texture = GetTexture();
	if (texture && a_Level < texture->GetNumLevels())
	{
		auto length = texture->GetDimensionByLevel(a_Level, 0);

		glTexSubImage1D(GL_TEXTURE_1D, a_Level, 0, length,
			m_ExternalFormat, m_ExternalType, &a_Data);
	}
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTexture1D::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE1D)
	{
		return std::make_shared<OpenGLTexture1D>(static_cast<Texture1D*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
