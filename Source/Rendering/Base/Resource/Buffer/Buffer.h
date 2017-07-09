#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/GraphicsResource.h>

NAMESPACE_MENGINE_BEGIN

class Buffer : public GraphicsResource
{
protected:
	Buffer(_U32 a_NumElements, size_t a_ElementSize, _U32 a_Type = GraphicsObject::BUFFER);
public:
	virtual ~Buffer();
};

NAMESPACE_MENGINE_END