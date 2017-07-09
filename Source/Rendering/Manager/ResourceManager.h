#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/RenderResource.h>
#include <Independent/DataStructure/MSet.h>

NAMESPACE_MENGINE_BEGIN

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool Insert(GraphicsObject* a_Object, std::shared_ptr<RenderResource> a_RenderResource);
	bool Get(GraphicsObject* a_Object, std::shared_ptr<RenderResource>& a_RenderResource) const;

private:
	MSet<GraphicsObject*, std::shared_ptr<RenderResource>> ResrouceMap;
};

NAMESPACE_MENGINE_END