#include <Rendering/Base/Resource/Texture/TextureCube.h>



Miracle::TextureCube::TextureCube(DataFormat a_Format, _U32 a_Length, bool a_HasMipmap)
	: TextureArray(CubeFaceCount,a_Format,2,a_Length,a_Length,1,a_HasMipmap,GraphicsObject::TEXTURE_CUBE)
{

}

Miracle::TextureCube::~TextureCube()
{
}

_U32 Miracle::TextureCube::GetLength() const
{
	return TextureArray::GetDimension(0);
}
