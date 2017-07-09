#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureRenderTarget.h>


Miracle::OpenGLTextureRenderTarget::OpenGLTextureRenderTarget(TextureRenderTarget* a_Texture)
	: OpenGLTexture2D(a_Texture)
{

}

Miracle::OpenGLTextureRenderTarget::~OpenGLTextureRenderTarget()
{

}


bool Miracle::OpenGLTextureRenderTarget::CanAutoGenerateMipmaps() const
{
	auto texture = GetTexture();

	return texture && texture->HasMipmaps() && texture->WantAutogenerateMipmaps();
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLTextureRenderTarget::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::TEXTURE_RENDER_TARGET)
	{
		return std::make_shared<OpenGLTextureRenderTarget>(static_cast<TextureRenderTarget*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}