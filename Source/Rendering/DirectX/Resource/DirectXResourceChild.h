#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Resource/RenderResource.h>

NAMESPACE_MENGINE_BEGIN

class DirectXResourceChild : public RenderResource
{
public:
	DirectXResourceChild(GraphicsObject* p_GraphicsResource);
	~DirectXResourceChild();

	inline ID3D11DeviceChild* GetHandle() const;

public:
	ID3D11DeviceChild* m_Handle;
};

inline ID3D11DeviceChild* Miracle::DirectXResourceChild::GetHandle() const
{
	return m_Handle;
}
NAMESPACE_MENGINE_END