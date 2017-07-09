#include <Rendering/Base/Resource/Texture/Texture3D.h>

Miracle::Texture3D::Texture3D(DataFormat a_Format, _U32 a_Width, _U32 a_Height, _U32 a_Depth, bool a_HasMipmap)
	: TextureSingle(a_Format, 3, a_Width, a_Height, a_Depth, a_HasMipmap, GraphicsObject::TEXTURE3D)
{

}

Miracle::Texture3D::~Texture3D()
{
}


_U32 Miracle::Texture3D::GetWidth() const
{
	return Texture::GetDimension(0);
}

_U32 Miracle::Texture3D::GetHeight() const
{
	return Texture::GetDimension(1);
}

_U32 Miracle::Texture3D::GetDepth() const
{
	return Texture::GetDimension(2);
}

