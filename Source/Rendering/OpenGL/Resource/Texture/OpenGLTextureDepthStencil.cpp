#include "OpenGLTextureDepthStencil.h"

Miracle::OpenGLTextureDepthStencil::OpenGLTextureDepthStencil(TextureDepthStencil* a_Texture)
	: OpenGLTexture2D(a_Texture)
{

}

Miracle::OpenGLTextureDepthStencil::~OpenGLTextureDepthStencil()
{
}

bool Miracle::OpenGLTextureDepthStencil::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTextureDepthStencil::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE_DEPTH_STENCIL)
	{
		return std::make_shared<OpenGLTextureDepthStencil>(static_cast<TextureDepthStencil*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
