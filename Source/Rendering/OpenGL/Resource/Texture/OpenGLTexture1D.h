#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureSingle.h>
#include <Rendering/Base/Resource/Texture/Texture1D.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTexture1D : public OpenGLTextureSingle
{
public:
	OpenGLTexture1D(Texture1D* a_Texture);
	virtual ~OpenGLTexture1D();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline Texture1D* GetTexure() const;

	virtual bool CanAutoGenerateMipmaps() const override;
protected:
	virtual void LoadTextureLevel(unsigned int a_Level, void* a_Data) override;
};

inline Texture1D* OpenGLTexture1D::GetTexure() const
{
	return static_cast<Texture1D*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END