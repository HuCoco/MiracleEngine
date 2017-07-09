#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture2D.h>
#include <Rendering/Base/Resource/Texture/TextureDepthStencil.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTextureDepthStencil : public OpenGLTexture2D
{
public:
	OpenGLTextureDepthStencil(TextureDepthStencil* a_Texture);
	~OpenGLTextureDepthStencil();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline TextureDepthStencil* GetTextureDepthStencil() const;

	virtual bool CanAutoGenerateMipmaps() const override;
};

inline TextureDepthStencil* OpenGLTextureDepthStencil::GetTextureDepthStencil() const
{
	return static_cast<TextureDepthStencil*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END