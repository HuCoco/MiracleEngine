#include <Rendering/Base/Resource/Texture/TextureCubeArray.h>



Miracle::TextureCubeArray::TextureCubeArray(_U32 a_NumCubes, DataFormat a_Format, _U32 a_Length, bool a_HasMipmap)
	: TextureArray(CubeFaceCount * a_NumCubes, a_Format, 2, a_Length, a_Length, 1, a_HasMipmap,GraphicsObject::TEXTURE_CUBE_ARRAY)
{

}

Miracle::TextureCubeArray::~TextureCubeArray()
{
}

_U32 Miracle::TextureCubeArray::GetNumCubes() const
{
	return m_NumCubes;
}

_U32 Miracle::TextureCubeArray::GetLength() const
{
	return TextureArray::GetDimension(0);
}
