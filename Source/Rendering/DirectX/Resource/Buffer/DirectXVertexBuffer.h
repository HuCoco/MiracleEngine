#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/DirectX/Resource/Buffer/DirectXBuffer.h>
#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>

NAMESPACE_MENGINE_BEGIN

class DirectXVertexBuffer : public DirectXBuffer
{
public:
	DirectXVertexBuffer(ID3D11Device* a_Device, VertexBuffer* a_Buffer);
	virtual ~DirectXVertexBuffer();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline VertexBuffer* GetVertexBuffer() const;

	void Enable(ID3D11DeviceContext* context);
	void Disable(ID3D11DeviceContext* context);
};

inline VertexBuffer* DirectXVertexBuffer::GetVertexBuffer() const
{
	return static_cast<VertexBuffer*>(m_pGraphicsObject);
}



NAMESPACE_MENGINE_END