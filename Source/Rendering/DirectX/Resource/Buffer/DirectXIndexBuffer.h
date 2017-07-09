#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/DirectX/Resource/Buffer/DirectXBuffer.h>
#include <Rendering/Base/Resource/Buffer/IndexBuffer.h>

NAMESPACE_MENGINE_BEGIN

class DirectXIndexBuffer : public DirectXBuffer
{
public:
	DirectXIndexBuffer(ID3D11Device* a_Device, IndexBuffer* a_Buffer);
	virtual ~DirectXIndexBuffer();

	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);

	inline IndexBuffer* GetIndexBuffer() const;
	inline DXGI_FORMAT GetDataFormat() const;

	void Enable(ID3D11DeviceContext* context);
	void Disable(ID3D11DeviceContext* context);

private:
	DXGI_FORMAT m_Format;
};

inline IndexBuffer* DirectXIndexBuffer::GetIndexBuffer() const
{
	return static_cast<IndexBuffer*>(m_pGraphicsObject);
}

inline DXGI_FORMAT DirectXIndexBuffer::GetDataFormat() const
{
	return m_Format;
}

NAMESPACE_MENGINE_END