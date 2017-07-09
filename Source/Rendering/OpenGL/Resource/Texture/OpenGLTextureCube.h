#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureArray.h>
#include <Rendering/Base/Resource/Texture/TextureCube.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTextureCube : public OpenGLTextureArray
{
public:
	OpenGLTextureCube(TextureCube* a_Texture);
	~OpenGLTextureCube();
	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline TextureCube* GetTexture() const;

	virtual bool CanAutoGenerateMipmaps() const override;
protected:
	virtual void LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data) override;
};

inline TextureCube* OpenGLTextureCube::GetTexture() const
{
	return static_cast<TextureCube*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END