#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>

NAMESPACE_MENGINE_BEGIN

class TextureDepthStencil : public Texture2D
{
public:
	TextureDepthStencil(DataFormat a_Format, _U32 a_Width, _U32 a_Height);
	virtual ~TextureDepthStencil();

	void MakeShaderInput();
	bool IsShaderInput();

private:
	bool m_ShaderInput;
};

NAMESPACE_MENGINE_END