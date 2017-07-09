#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureArray.h>
#include <Rendering/Base/Resource/Texture/Texture2DArray.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTexture2DArray : public OpenGLTextureArray
{
public:
	OpenGLTexture2DArray(Texture2DArray* a_Texture);
	~OpenGLTexture2DArray();
	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline Texture2DArray* GetTexture() const;

	virtual bool CanAutoGenerateMipmaps() const override;
protected:
	virtual void LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data) override;
};

inline Texture2DArray* OpenGLTexture2DArray::GetTexture() const
{
	return static_cast<Texture2DArray*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END