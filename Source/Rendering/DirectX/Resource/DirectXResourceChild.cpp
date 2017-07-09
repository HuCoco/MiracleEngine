#include <Rendering/DirectX/Resource/DirectXResourceChild.h>



Miracle::DirectXResourceChild::DirectXResourceChild(GraphicsObject* p_GraphicsResource)
	: RenderResource(p_GraphicsResource)
	, m_Handle(nullptr)
{

}

Miracle::DirectXResourceChild::~DirectXResourceChild()
{
}
