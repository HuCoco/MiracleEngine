#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/GraphicsResource.h>
NAMESPACE_MENGINE_BEGIN


class RenderResource
{
public:
	RenderResource(GraphicsObject* a_GraphicsResource);
	virtual ~RenderResource();

	inline GraphicsResource* GetGraphicsResource() const;
	inline GraphicsObject* GetGraphicsObject() const;
protected:
	GraphicsObject* m_pGraphicsObject;
};

inline GraphicsResource* RenderResource::GetGraphicsResource() const
{
	return static_cast<GraphicsResource*>(m_pGraphicsObject);
}

inline GraphicsObject* RenderResource::GetGraphicsObject() const
{
	return m_pGraphicsObject;
}

NAMESPACE_MENGINE_END