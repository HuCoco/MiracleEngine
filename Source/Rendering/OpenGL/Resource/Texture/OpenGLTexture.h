#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/OpenGLResource.h>
#include <Rendering/Base/Resource/Texture/Texture.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTexture : public OpenGLResource
{
protected:
	OpenGLTexture(Texture* a_Texture, GLenum a_Target, GLenum a_TargetBinding);
public:
	virtual ~OpenGLTexture();

	inline Texture* GetTexture() const;
	inline GLenum GetTarget() const;
	inline GLenum GetTargetBinding() const;

	inline static GLuint GetInternalFormat(DataFormat a_Format);

protected:
	GLenum m_Target;
	GLenum m_TargetBinding;

	GLuint m_NumLevels;
	GLuint m_InternalFormat;
	GLuint m_ExternalFormat;
	GLuint m_ExternalType;

	static const GLuint OpenGLTextureInternalFormat[DataFormat::NUM_DIRECTX_FORMATS];
	static const GLuint OpenGLTextureExternalFormat[DataFormat::NUM_DIRECTX_FORMATS];
	static const GLuint OpenGLTextureExternalType[MiracleChannels::NUM_CHANNELS];
};

inline Texture* OpenGLTexture::GetTexture() const
{
	return static_cast<Texture*>(m_pGraphicsObject);
}

inline GLenum OpenGLTexture::GetTarget() const
{
	return m_Target;
}

inline GLenum OpenGLTexture::GetTargetBinding() const
{
	return m_TargetBinding;
}

inline GLuint OpenGLTexture::GetInternalFormat(DataFormat a_Format)
{
	return OpenGLTextureInternalFormat[a_Format];
}
NAMESPACE_MENGINE_END