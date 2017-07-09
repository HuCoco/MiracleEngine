#include "OpenGLRenderTarget.h"

GLuint rboDepth;


Miracle::OpenGLRenderTarget::OpenGLRenderTarget(RenderTarget* a_RenderTarget,
	std::vector<OpenGLTextureRenderTarget*>& a_RenderTargetTextures, OpenGLTextureDepthStencil* a_DepthTargetTexture)
	: RenderTargetResource(a_RenderTarget)
	, m_RenderTargetTextures(a_RenderTargetTextures)
	, m_DepthStencilTexture(a_DepthTargetTexture)
	, m_FrameBuffer(0)
{
	MENGINE_ASSERT_MSG(a_RenderTarget->GetNumTargets() <= m_RenderTargetTextures.size(),
		"DrawTargets has more targets than there are RT textures provided.");
	glGenFramebuffers(1, &m_FrameBuffer);
	glGenRenderbuffers(1, &rboDepth);
}

Miracle::OpenGLRenderTarget::~OpenGLRenderTarget()
{
	glDeleteFramebuffers(1, &m_FrameBuffer);
}

std::shared_ptr<Miracle::RenderTargetResource> Miracle::OpenGLRenderTarget::Create(RenderTarget* a_RenderTarget,
	std::vector<RenderResource*>& a_RenderTargetTextures, RenderResource* a_DepthTargetTextures)
{
	std::vector<OpenGLTextureRenderTarget*> RTTextures(a_RenderTargetTextures.size());
	for (size_t i = 0; i < a_RenderTargetTextures.size(); ++i)
	{
		RTTextures[i] = static_cast<OpenGLTextureRenderTarget*>(a_RenderTargetTextures[i]);
	}
	OpenGLTextureDepthStencil* dxDSTexture = static_cast<OpenGLTextureDepthStencil*>(a_DepthTargetTextures);
	return std::make_shared<OpenGLRenderTarget>(a_RenderTarget, RTTextures, dxDSTexture);
}

void Miracle::OpenGLRenderTarget::Enable()
{
	GLint intVals[4];
	GLdouble doubleVals[2];
	glGetIntegerv(GL_VIEWPORT, intVals);
	glGetDoublev(GL_DEPTH_RANGE, doubleVals);
	m_SaveViewportX = intVals[0];
	m_SaveViewportY = intVals[1];
	m_SaveViewportWidth = intVals[2];
	m_SaveViewportHeight = intVals[3];
	m_SaveViewportNear = doubleVals[0];
	m_SaveViewportFar = doubleVals[1];

	auto viewportWidth = static_cast<GLsizei>(m_Target->GetWidth());
	auto viewportHeight = static_cast<GLsizei>(m_Target->GetHeight());
	glViewport(0, 0, viewportWidth, viewportHeight);
	glDepthRange(0.0, 1.0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FrameBuffer);

	const auto numTargets = m_Target->GetNumTargets();
	std::vector<GLenum> useDrawBuffers(numTargets);
	for (unsigned i = 0; i < numTargets; ++i)
	{
		auto colorTarget = GL_COLOR_ATTACHMENT0 + i;

		useDrawBuffers[i] = colorTarget;

		auto textureRT = m_RenderTargetTextures[i];
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, colorTarget, GL_TEXTURE_2D, textureRT->GetHandle(), 0);
	}

	if (m_DepthStencilTexture)
	{

		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1920, 1080);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
		//glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthStencilTexture->GetHandle(), 0);
	}
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
 		MENGINE_ASSERT_MSG(false, "DepthStencilBuffer Error.");
	}

	glDrawBuffers(static_cast<GLsizei>(useDrawBuffers.size()), useDrawBuffers.data());
}

void Miracle::OpenGLRenderTarget::Disable()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(m_SaveViewportX, m_SaveViewportY, m_SaveViewportWidth, m_SaveViewportHeight);
	glDepthRange(m_SaveViewportNear, m_SaveViewportFar);

	auto const numTargets = m_Target->GetNumTargets();
	for (unsigned i = 0; i < numTargets; ++i)
	{
		auto textureRT = m_RenderTargetTextures[i];
		if (textureRT->CanAutoGenerateMipmaps())
		{
			textureRT->GenerateMipmaps();
		}
	}
}

void Miracle::OpenGLRenderTarget::EnableDepthStencilBuffer()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FrameBuffer);
	glBlitFramebuffer(
		0, 0, GetRenderTarget()->GetWidth(), GetRenderTarget()->GetHeight(),
		0, 0, GetRenderTarget()->GetWidth(), GetRenderTarget()->GetHeight(),
		GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Miracle::OpenGLRenderTarget::DisableDepthStencilBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
