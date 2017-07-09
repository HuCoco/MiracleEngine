#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture1DArray.h>


Miracle::OpenGLTexture1DArray::OpenGLTexture1DArray(Texture1DArray* a_Texture)
	: OpenGLTextureArray(a_Texture, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY)
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_1D_ARRAY, m_Handle);

	const auto length = a_Texture->GetDimension(0);
	const auto numItems = a_Texture->GetNumItems();
	glTexStorage2D(GL_TEXTURE_1D_ARRAY, m_NumLevels, m_InternalFormat, length, numItems);

	Initialize();

	glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
}

Miracle::OpenGLTexture1DArray::~OpenGLTexture1DArray()
{

}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTexture1DArray::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE1D_ARRAY)
	{
		return std::make_shared<OpenGLTexture1DArray>(static_cast<Texture1DArray*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

bool Miracle::OpenGLTexture1DArray::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

void Miracle::OpenGLTexture1DArray::LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data)
{
	auto texture = GetTexture();
	if (texture && a_Level < texture->GetNumLevels())
	{
		auto const length = texture->GetDimensionByLevel(a_Level, 0);

		glTexSubImage2D(GL_TEXTURE_1D_ARRAY, a_Level, 0, a_Item, length, 1,
			m_ExternalFormat, m_ExternalType, a_Data);
	}
}

