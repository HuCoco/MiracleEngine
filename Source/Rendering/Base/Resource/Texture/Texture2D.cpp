#include <Rendering/Base/Resource/Texture/Texture2D.h>



Miracle::Texture2D::Texture2D(DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap)
	: TextureSingle(a_Format, 2, a_Width, a_Height, 1, a_HasMipmap, GraphicsObject::TEXTURE2D)
	, m_Shared(false)
{

}

Miracle::Texture2D::Texture2D(DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap, _U32 a_Type)
	: TextureSingle(a_Format, 2, a_Width, a_Height, 1, a_HasMipmap,a_Type)
	, m_Shared(false)
{

}

Miracle::Texture2D::~Texture2D()
{

}

_U32 Miracle::Texture2D::GetWidth() const
{
	return Texture::GetDimension(0);
}

_U32 Miracle::Texture2D::GetHeight() const
{
	return Texture::GetDimension(1);
}

void Miracle::Texture2D::MakeShared()
{
	m_Usage = GraphicsResource::Usage::DEFAULT;
	m_Shared = true;
}

bool Miracle::Texture2D::IsShared() const
{
	return m_Shared;
}
