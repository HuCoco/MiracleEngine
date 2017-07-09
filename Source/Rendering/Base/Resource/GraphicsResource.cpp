#include <Rendering/Base/Resource/GraphicsResource.h>



Miracle::GraphicsResource::GraphicsResource(_U32 a_NumElements, size_t a_ElementSize,_U32 a_Type /* = GraphicsObject::GRAPHICS_RESOURCE */)
	: GraphicsObject(a_Type)
	, m_NumElements(a_NumElements)
	, m_ElementSize(a_ElementSize)
	, m_Usage(Usage::IMMUTABLE)
	, m_AccessFlag(AccessFlag::NONE)
	, m_Offset(0)
	, m_pData(nullptr)
{
	if (m_NumElements > 0)
	{
		if (m_ElementSize > 0)
		{
			m_NumBytes = m_NumElements * m_ElementSize;
			m_NumActiveElements = m_NumElements;
		}
		else
		{
			m_NumBytes = 0;
			m_NumActiveElements = m_NumElements;
		}
	}
	else
	{
		m_NumBytes = 0;
		m_ElementSize = 0;	
		m_NumActiveElements = 0;
	}
}

Miracle::GraphicsResource::~GraphicsResource()
{
}

void Miracle::GraphicsResource::SetOffset(_U32 a_Offset)
{
	if (a_Offset < m_NumElements)
	{
		m_Offset = a_Offset;
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Invalid Offset.");
		m_Offset = 0;
	}
}
