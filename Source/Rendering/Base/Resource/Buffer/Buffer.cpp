#include "Buffer.h"


Miracle::Buffer::Buffer(_U32 a_NumElements, size_t a_ElementSize, _U32 a_Type /*= GraphicsObject::BUFFER*/)
	: GraphicsResource(a_NumElements,a_ElementSize,a_Type)
{

}

Miracle::Buffer::~Buffer()
{

}
