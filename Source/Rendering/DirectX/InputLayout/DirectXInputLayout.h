#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Shaders/Shader.h>
#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>

NAMESPACE_MENGINE_BEGIN

class DirectXInputLayout
{
public:
	DirectXInputLayout(ID3D11Device* a_Device, VertexBuffer* a_VertexBuffer, Shader* a_Shader);
	~DirectXInputLayout();

	void Enable(ID3D11DeviceContext* context);
	void Disable(ID3D11DeviceContext* context);

private:
	ID3D11InputLayout* m_Layout;
	_U32 m_NumElements;
	D3D11_INPUT_ELEMENT_DESC mElements[16];
	std::string mName;

	static char const* m_Semantic[16];
};

NAMESPACE_MENGINE_END