#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTextureArray : public DirectXTexture
{
protected:
	DirectXTextureArray(TextureArray* a_Texture);

public:
	~DirectXTextureArray();

	inline TextureArray* GetTexture() const;
};

inline TextureArray* DirectXTextureArray::GetTexture() const
{
	return static_cast<TextureArray*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END