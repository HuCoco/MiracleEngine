#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture2DArray.h>

Miracle::OpenGLTexture2DArray::OpenGLTexture2DArray(Texture2DArray* a_Texture)
	: OpenGLTextureArray(a_Texture, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY)
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_Handle);

	const auto width = a_Texture->GetDimension(0);
	const auto height = a_Texture->GetDimension(1);
	const auto numItems = a_Texture->GetNumItems();
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, m_NumLevels, m_InternalFormat, width, height, numItems);

	Initialize();

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

Miracle::OpenGLTexture2DArray::~OpenGLTexture2DArray()
{
}

void Miracle::OpenGLTexture2DArray::LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data)
{
	auto texture = GetTexture();
	if (texture && a_Level < texture->GetNumLevels())
	{
		const auto width = texture->GetDimensionByLevel(a_Level, 0);
		const auto height = texture->GetDimensionByLevel(a_Level, 1);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, a_Level, 0, 0, a_Item, width, height, 1,
			m_ExternalFormat, m_ExternalType, a_Data);
	}
}

bool Miracle::OpenGLTexture2DArray::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTexture2DArray::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE2D_ARRAY)
	{
		return std::make_shared<OpenGLTexture2DArray>(static_cast<Texture2DArray*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
