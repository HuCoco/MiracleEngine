#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>

NAMESPACE_MENGINE_BEGIN

class Texture1D : public TextureSingle
{
public:
	Texture1D(DataFormat a_Format,_U32 a_Length,bool a_HasMipmap);
	virtual ~Texture1D();

	_U32 GetLength() const;
};

NAMESPACE_MENGINE_END