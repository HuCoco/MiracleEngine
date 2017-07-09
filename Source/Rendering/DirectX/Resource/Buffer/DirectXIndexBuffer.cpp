#include <Rendering/DirectX/Resource/Buffer/DirectXIndexBuffer.h>

Miracle::DirectXIndexBuffer::DirectXIndexBuffer(ID3D11Device* a_Device, IndexBuffer* a_Buffer)
	: DirectXBuffer(a_Buffer)
	, m_Format(a_Buffer->GetElementSize() == 4 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = a_Buffer->GetNumBytes();
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
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
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	}

	ID3D11Buffer* buffer = nullptr;
	HRESULT hr = S_OK;
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
	CHECK_HR_RETURN_NONE("Failed to create index buffer");
	m_Handle = buffer;
}

Miracle::DirectXIndexBuffer::~DirectXIndexBuffer()
{

}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXIndexBuffer::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::INDEX_BUFFER)
	{
		return std::make_shared<DirectXIndexBuffer>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<IndexBuffer*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}

void Miracle::DirectXIndexBuffer::Enable(ID3D11DeviceContext* a_Context)
{
	if (m_Handle)
	{
		ID3D11Buffer* dxBuffer = static_cast<ID3D11Buffer*>(m_Handle);
		a_Context->IASetIndexBuffer(dxBuffer, m_Format, 0);
	}
}

void Miracle::DirectXIndexBuffer::Disable(ID3D11DeviceContext* a_Context)
{
	if (m_Handle)
	{
		a_Context->IASetIndexBuffer(0, DXGI_FORMAT_UNKNOWN, 0);
	}
}
