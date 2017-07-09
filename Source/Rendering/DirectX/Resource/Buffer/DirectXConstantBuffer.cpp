#include <Rendering/DirectX/Resource/Buffer/DirectXConstantBuffer.h>



Miracle::DirectXConstantBuffer::DirectXConstantBuffer(ID3D11Device* a_Device, ConstantBuffer* a_ConstantBuffer)
	: DirectXBuffer(a_ConstantBuffer)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = a_ConstantBuffer->GetNumBytes();
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.MiscFlags = D3D11_RESOURCE_MISC_NONE;
	desc.StructureByteStride = 0;
	GraphicsResource::Usage usage = a_ConstantBuffer->GetUsage();
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
	if (a_ConstantBuffer->GetData())
	{
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = a_ConstantBuffer->GetData();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		hr = a_Device->CreateBuffer(&desc, &data, &buffer);
	}
	else
	{
		hr = a_Device->CreateBuffer(&desc, nullptr, &buffer);
	}
	CHECK_HR_RETURN_NONE("Failed to create constant buffer");
	m_Handle = buffer;
}

Miracle::DirectXConstantBuffer::~DirectXConstantBuffer()
{

}

std::shared_ptr<Miracle::RenderResource> Miracle::DirectXConstantBuffer::Create(void* a_Device, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::CONSTANT_BUFFER)
	{
		return std::make_shared<DirectXConstantBuffer>(reinterpret_cast<ID3D11Device*>(a_Device), static_cast<ConstantBuffer*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
