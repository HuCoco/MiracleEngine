#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLTextureSingle : public OpenGLTexture
{
protected:
	OpenGLTextureSingle(TextureSingle* a_Texture, GLenum a_Target, GLenum a_TargetBinding);
public:
	~OpenGLTextureSingle();

	inline TextureSingle* GetTexture() const;

	virtual bool Update() override;
	virtual bool CopyMem2GraphMem() override;
	virtual bool CopyGraphMem2Mem() override;
	bool Update(_U32 a_Level);
	bool CopyMem2GraphMem(_U32 level);
	bool CopyGraphMem2Mem(_U32 level);


	virtual bool CanAutoGenerateMipmaps() const = 0;
	virtual bool GenerateMipmaps();
protected:
	void Initialize();
	virtual void LoadTextureLevel(_U32 a_Level, void* a_Data) = 0;
	bool DoCopyMem2GraphMem(unsigned int level);
private:

	GLuint m_LevelPixelUnpackBuffer[Texture::MAX_MIPMAP_LEVELS];
	GLuint m_LevelPixelPackBuffer[Texture::MAX_MIPMAP_LEVELS];
};

inline TextureSingle* OpenGLTextureSingle::GetTexture() const
{
	return static_cast<TextureSingle*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END