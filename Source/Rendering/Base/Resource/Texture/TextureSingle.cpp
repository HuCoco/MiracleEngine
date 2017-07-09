#include <Rendering/Base/Resource/Texture/TextureSingle.h>



Miracle::TextureSingle::TextureSingle(DataFormat a_Format, _U32 a_NumDimensions, _U32 a_Dimension1, _U32 a_Dimension2, _U32 a_Dimension3, bool a_HasMipmap,
	_U32 a_Type /*= GraphicsObject::TEXTURE_SINGLE*/)
	: Texture(1,a_Format,a_NumDimensions,a_Dimension1,a_Dimension2,a_Dimension3,a_HasMipmap,a_Type)
{

}

Miracle::TextureSingle::~TextureSingle()
{
}
