#include <Rendering/Base/GraphicsObject.h>


Miracle::GraphicsObject::GraphicsObject(_U32 a_Type)
	: HObject(HObject::HObjectType::GRAPHICS_OBJECT)
	, m_GraphicsType(a_Type)
{
	if (a_Type < GRAPHICS_RESOURCE || a_Type >= NUM_GRAPHICS_OBJECT_TYPES)
	{
		MENGINE_ASSERT_MSG(false, "maybe input a error graphics type.");
		m_GraphicsType = GRAPHICS_RESOURCE;
	}
}

Miracle::GraphicsObject::~GraphicsObject()
{
}
