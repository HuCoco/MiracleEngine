#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>

NAMESPACE_MENGINE_BEGIN

class Texture2DArray : public TextureArray
{
public:
	Texture2DArray(_U32 a_NumItems, DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap);
	~Texture2DArray();

	_U32 GetWidth() const;
	_U32 GetHeight() const;
};

NAMESPACE_MENGINE_END