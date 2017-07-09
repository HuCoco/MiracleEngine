#include "TextureArray.h"



Miracle::TextureArray::TextureArray(_U32 a_NumItems, DataFormat a_Format, _U32 a_NumDimensions,
	_U32 a_Dimension1, _U32 a_Dimension2, _U32 a_Dimension3, bool a_HasMipmap, _U32 a_Type /*= GraphicsObject::TEXTURE_ARRAY*/)
	: Texture(a_NumItems, a_Format, a_NumDimensions, a_Dimension1, a_Dimension2, a_Dimension3, a_HasMipmap, a_Type)
{

}

Miracle::TextureArray::~TextureArray()
{
}
