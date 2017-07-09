#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureSingle.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTexture2D : public OpenGLTextureSingle
{
public:
	OpenGLTexture2D(Texture2D* a_Texture);
	~OpenGLTexture2D();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline Texture2D* GetTexure() const;

	virtual bool CanAutoGenerateMipmaps() const override;
protected:
	virtual void LoadTextureLevel(unsigned int a_Level, void* a_Data) override;
};

inline Texture2D* OpenGLTexture2D::GetTexure() const
{
	return static_cast<Texture2D*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END