#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>

NAMESPACE_MENGINE_BEGIN

class Texture2D : public TextureSingle
{
public:
	Texture2D(DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap);
	virtual ~Texture2D();

	_U32 GetWidth() const;
	_U32 GetHeight() const;

	void MakeShared();
	bool IsShared() const;

protected:
	Texture2D(DataFormat a_Format, _U32 a_Width, _U32 a_Height, bool a_HasMipmap,_U32 a_Type);

protected:
	bool m_Shared;
	
};

NAMESPACE_MENGINE_END