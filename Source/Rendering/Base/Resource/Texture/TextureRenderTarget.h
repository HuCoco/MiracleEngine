#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>

NAMESPACE_MENGINE_BEGIN

class TextureRenderTarget : public Texture2D
{
public:
	TextureRenderTarget(DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap);
	virtual ~TextureRenderTarget();
};

NAMESPACE_MENGINE_END