#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>

NAMESPACE_MENGINE_BEGIN

class Texture3D : public TextureSingle
{
public:
	Texture3D(DataFormat a_Format,_U32 a_Width,_U32 a_Height,_U32 a_Thickness,bool a_HasMipmap);
	virtual ~Texture3D();

	_U32 GetWidth() const;
	_U32 GetHeight() const;
	_U32 GetDepth() const;
};

NAMESPACE_MENGINE_END
