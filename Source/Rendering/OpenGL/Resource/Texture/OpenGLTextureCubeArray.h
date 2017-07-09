#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureArray.h>
#include <Rendering/Base/Resource/Texture/TextureCubeArray.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTextureCubeArray : public OpenGLTextureArray
{
public:
	OpenGLTextureCubeArray(TextureCubeArray* a_Texture);
	~OpenGLTextureCubeArray();
	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline TextureCubeArray* GetTexture() const;

	virtual bool CanAutoGenerateMipmaps() const override;
protected:
	virtual void LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data) override;
};

inline TextureCubeArray* OpenGLTextureCubeArray::GetTexture() const
{
	return static_cast<TextureCubeArray*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END
