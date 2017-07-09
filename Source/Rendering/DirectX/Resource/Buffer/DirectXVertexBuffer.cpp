#include "DirectXVertexBuffer.h"



Miracle::DirectXVertexBuffer::DirectXVertexBuffer(ID3D11Device* a_Device, VertexBuffer* a_Buffer)
	: DirectXBuffer(a_Buffer)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = a_Buffer->GetNumBytes();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.MiscFlags = D3D11_RESOURCE_MISC_NONE;
	desc.StructureByteStride = 0;
	GraphicsResource::Usage usage = a_Buffer->GetUsage();
	if (usage == GraphicsResource::Usage::IMMUTABLE)
	{
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	}
	else if (usage == GraphicsResource::Usage::DYNAMIC)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Vertex output streams are not yet tested.");
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags |= D3D11_BIND_STREAM_OUTPUT;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	}
	ID3D11Buffer* buffer = nullptr;
	HRESULT hr;
	if (a_Buffer->GetData())
	{
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = a_Buffer->GetData();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		hr = a_Device->CreateBuffer(&desc, &data, &buffer);
	}
	else
	{
		hr = a_Device->CreateBuffer(&desc, nullptr, &buffer);
	}
	CHECK_HR_RETURN_NONE("Failed to create vertex buffer");
	m_Handle = buffer;
}

Miracle::DirectXVertexBuffer::~DirectXVertexBuffer()
{
}

void Miracle::DirectXVertexBuffer::Enable(ID3D11DeviceContext* context)
{
	if (m_Handle)
	{
		ID3D11Buffer* buffers[1] = { GetDirectXBuffer() };
		VertexBuffer* vbuffer = GetVertexBuffer();
		UINT strides[1] = { vbuffer->GetElementSize() };
		UINT offsets[1] = { 0 };
		context->IASetVertexBuffers(0, 1, buffers, strides, offsets);
	}
}

void Miracle::DirectXVertexBuffer::Disable(ID3D11DeviceContext* context)
{
	if (m_Handle)
	{
		ID3D11Buffer* buffers[1] = { nullptr };
		UINT strides[1] = { 0 };
		UINT offsets[1] = { 0 };
		context->IASetVertexBuffers(0, 1, buffers, strides, offsets);
	}
}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXVertexBuffer::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::VERTEX_BUFFER)
	{
		return std::make_shared<DirectXVertexBuffer>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<VertexBuffer*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
