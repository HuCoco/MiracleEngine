#include <Rendering/Base/Resource/Texture/TextureRenderTarget.h>

Miracle::TextureRenderTarget::TextureRenderTarget(DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap)
	: Texture2D(a_Format,a_Width,a_Height,a_HasMipmap,GraphicsObject::TEXTURE_RENDER_TARGET)
{

}

Miracle::TextureRenderTarget::~TextureRenderTarget()
{
}
