#include <Rendering/Base/Resource/Texture/Texture1DArray.h>


Miracle::Texture1DArray::Texture1DArray(_U32 a_NumItems, DataFormat a_Format, _U32 a_Length, bool a_HasMipmap)
	: TextureArray(a_NumItems, a_Format, 1, a_Length, 1, 1, a_HasMipmap, GraphicsObject::TEXTURE1D_ARRAY)
{
}

Miracle::Texture1DArray::~Texture1DArray()
{
}

_U32 Miracle::Texture1DArray::GetLength() const
{
	return TextureArray::GetDimension(0);
}
