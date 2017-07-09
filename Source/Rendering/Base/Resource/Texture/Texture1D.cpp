#include <Rendering/Base/Resource/Texture/Texture1D.h>


Miracle::Texture1D::Texture1D(DataFormat a_Format, _U32 a_Length, bool a_HasMipmap)
	:TextureSingle(a_Format, 1, a_Length, 1, 1, a_HasMipmap, GraphicsObject::TEXTURE1D)
{

}

Miracle::Texture1D::~Texture1D()
{
}

_U32 Miracle::Texture1D::GetLength() const
{
	return Texture::GetDimension(0);
}
