#include <Rendering/Manager/ResourceManager.h>



Miracle::ResourceManager::ResourceManager()
{
}


Miracle::ResourceManager::~ResourceManager()
{
}

bool Miracle::ResourceManager::Insert(GraphicsObject* a_Object, std::shared_ptr<RenderResource> a_RenderResource)
{
	return ResrouceMap.Insert(a_Object, a_RenderResource);
}

bool Miracle::ResourceManager::Get(GraphicsObject* a_Object, std::shared_ptr<RenderResource>& a_RenderResource) const
{
	auto node = ResrouceMap.Find(a_Object);
	if (node == nullptr)
	{
		return false;
	}
	a_RenderResource = node->Value;
	return true;
}
