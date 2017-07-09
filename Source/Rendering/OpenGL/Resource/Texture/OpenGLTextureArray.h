#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTextureArray : public OpenGLTexture
{
protected:
	OpenGLTextureArray(TextureArray* a_Texture, GLenum a_Target, GLenum a_TargetBinding);

public:
	~OpenGLTextureArray();

	inline TextureArray* GetTexture() const;

	virtual bool Update() override;
	virtual bool CopyMem2GraphMem() override;
	virtual bool CopyGraphMem2Mem() override;
	bool Update(_U32 a_Item, _U32 a_Level);
	bool CopyMem2GraphMem(_U32 item, _U32 level);
	bool CopyGraphMem2Mem(_U32 item, _U32 level);
	virtual bool CanAutoGenerateMipmaps() const = 0;

	virtual bool GenerateMipmaps();

protected:
	void Initialize();

	virtual void LoadTextureLevel(_U32 item, _U32 level, const void* data) = 0;

	bool DoCopyMem2GraphMem(_U32 item, _U32 level);

	static GLenum const CubeFaceTarget[6];

private:
	GLuint m_LevelPixelUnpackBuffer[Texture::MAX_MIPMAP_LEVELS];
	GLuint m_LevelPixelPackBuffer[Texture::MAX_MIPMAP_LEVELS];
};

inline TextureArray* OpenGLTextureArray::GetTexture() const
{
	return static_cast<TextureArray*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END