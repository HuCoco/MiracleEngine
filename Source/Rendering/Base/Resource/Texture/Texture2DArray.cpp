#include <Rendering/Base/Resource/Texture/Texture2DArray.h>


Miracle::Texture2DArray::Texture2DArray(_U32 a_NumItems, DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap)
	: TextureArray(a_NumItems, a_Format, 2, a_Width, a_Height, 1, a_HasMipmap, GraphicsObject::TEXTURE2D_ARRAY)
{

}

Miracle::Texture2DArray::~Texture2DArray()
{
}

_U32 Miracle::Texture2DArray::GetWidth() const
{
	return TextureArray::GetDimension(0);
}

_U32 Miracle::Texture2DArray::GetHeight() const
{
	return TextureArray::GetDimension(1);
}
