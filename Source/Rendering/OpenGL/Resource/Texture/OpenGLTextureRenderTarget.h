#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture2D.h>
#include <Rendering/Base/Resource/Texture/TextureRenderTarget.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTextureRenderTarget : public OpenGLTexture2D
{
public:
	OpenGLTextureRenderTarget(TextureRenderTarget* a_Texture);
	~OpenGLTextureRenderTarget();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline TextureRenderTarget* GetTextureRenderTarget() const;

	virtual bool CanAutoGenerateMipmaps() const override;
};

inline TextureRenderTarget* OpenGLTextureRenderTarget::GetTextureRenderTarget() const
{
	return static_cast<TextureRenderTarget*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END