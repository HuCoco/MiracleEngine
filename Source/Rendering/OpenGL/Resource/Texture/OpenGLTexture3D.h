#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureSingle.h>
#include <Rendering/Base/Resource/Texture/Texture3D.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTexture3D : public OpenGLTextureSingle
{
public:
	OpenGLTexture3D(Texture3D* a_Texture);
	~OpenGLTexture3D();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline Texture3D* GetTexure() const;

	virtual bool CanAutoGenerateMipmaps() const override;
protected:
	virtual void LoadTextureLevel(unsigned int a_Level, void* a_Data) override;
};

inline Texture3D* OpenGLTexture3D::GetTexure() const
{
	return static_cast<Texture3D*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END