#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>

NAMESPACE_MENGINE_BEGIN

class DirectXTextureSingle : public DirectXTexture
{
protected:
	DirectXTextureSingle(TextureSingle* a_Texture);
public:
	~DirectXTextureSingle();

	inline TextureSingle* GetTexture() const;

};

inline TextureSingle* DirectXTextureSingle::GetTexture() const
{
	return static_cast<TextureSingle*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END