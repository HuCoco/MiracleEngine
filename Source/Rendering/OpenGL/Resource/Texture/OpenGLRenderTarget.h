#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Rendering/Base/Resource/RenderTargetResource.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureRenderTarget.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureDepthStencil.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLRenderTarget : public RenderTargetResource
{
public:
	OpenGLRenderTarget(RenderTarget* a_RenderTarget,std::vector<OpenGLTextureRenderTarget*>& a_RenderTargetTexures,
						OpenGLTextureDepthStencil* a_DepthTargetTexures);
	~OpenGLRenderTarget();

	static std::shared_ptr<RenderTargetResource> Create(RenderTarget* a_RenderTarget,
		std::vector<RenderResource*>& a_RenderTargetTextures, RenderResource* a_DepthTargetTextures);

	inline OpenGLTextureRenderTarget* GetRenderTargetTexture(_U32 i);
	inline OpenGLTextureDepthStencil* GetDepthStencilTexture();

	void Enable();
	void Disable();
	void EnableDepthStencilBuffer();
	void DisableDepthStencilBuffer();
private:
	std::vector<OpenGLTextureRenderTarget*> m_RenderTargetTextures;
	OpenGLTextureDepthStencil* m_DepthStencilTexture;

	GLuint m_FrameBuffer;


	GLint m_SaveViewportX;
	GLint m_SaveViewportY;
	GLsizei m_SaveViewportWidth;
	GLsizei m_SaveViewportHeight;
	GLdouble m_SaveViewportNear;
	GLdouble m_SaveViewportFar;
};

inline OpenGLTextureRenderTarget* OpenGLRenderTarget::GetRenderTargetTexture(_U32 i)
{
	return m_RenderTargetTextures[i];
}

inline OpenGLTextureDepthStencil* OpenGLRenderTarget::GetDepthStencilTexture()
{
	return m_DepthStencilTexture;
}

NAMESPACE_MENGINE_END