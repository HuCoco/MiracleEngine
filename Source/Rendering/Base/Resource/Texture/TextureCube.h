#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>

NAMESPACE_MENGINE_BEGIN

class TextureCube : public TextureArray
{
public:
	TextureCube(DataFormat a_Format, _U32 a_Length, bool a_HasMipmap);
	~TextureCube();

	_U32 GetLength() const;
};

NAMESPACE_MENGINE_END