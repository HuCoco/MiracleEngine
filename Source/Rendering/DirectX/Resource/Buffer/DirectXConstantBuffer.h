#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/DirectX/Resource/Buffer/DirectXBuffer.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>

NAMESPACE_MENGINE_BEGIN

class DirectXConstantBuffer : public DirectXBuffer
{
public:
	DirectXConstantBuffer(ID3D11Device* a_Device, ConstantBuffer* a_ConstantBuffer);
	virtual ~DirectXConstantBuffer();
	static std::shared_ptr<RenderResource> Create(void* a_Device, GraphicsObject* a_GraphicsResource);
};

NAMESPACE_MENGINE_END