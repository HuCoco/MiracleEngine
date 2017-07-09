#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>

NAMESPACE_MENGINE_BEGIN

class Texture1DArray : public TextureArray
{
public:
	Texture1DArray(_U32 a_NumItems, DataFormat a_Format, _U32 a_Length, bool a_HasMipmap);
	~Texture1DArray();

	_U32 GetLength() const;
};

NAMESPACE_MENGINE_END