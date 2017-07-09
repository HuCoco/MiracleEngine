#include <Rendering/Base/Resource/Texture/TextureDepthStencil.h>




Miracle::TextureDepthStencil::TextureDepthStencil(DataFormat a_Format, _U32 a_Width, _U32 a_Height)
	: Texture2D(DataFormatUtils::IsDepth(a_Format) ? a_Format : MENGINE_D24_UNORM_S8_UINT, a_Width, a_Height, false, GraphicsObject::TEXTURE_DEPTH_STENCIL)
	, m_ShaderInput(false)
{

}

Miracle::TextureDepthStencil::~TextureDepthStencil()
{
}

void Miracle::TextureDepthStencil::MakeShaderInput()
{
	m_ShaderInput = true;
}

bool Miracle::TextureDepthStencil::IsShaderInput()
{
	return m_ShaderInput;
}
