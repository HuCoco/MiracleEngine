#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureArray.h>
#include <Rendering/Base/Resource/Texture/Texture1DArray.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTexture1DArray : public OpenGLTextureArray
{
public:
	OpenGLTexture1DArray(Texture1DArray* a_Texture);
	~OpenGLTexture1DArray();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline Texture1DArray* GetTexture() const;

	virtual bool CanAutoGenerateMipmaps() const override;
protected:
	virtual void LoadTextureLevel(_U32 a_Item, _U32 a_Level, const void* a_Data) override;
};

inline Texture1DArray* OpenGLTexture1DArray::GetTexture() const
{
	return static_cast<Texture1DArray*>(m_pGraphicsObject);
}


NAMESPACE_MENGINE_END