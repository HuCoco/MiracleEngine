#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>

const size_t Miracle::ConstantBuffer::ALIGNMENT = 16;

Miracle::ConstantBuffer::ConstantBuffer(size_t a_NumBytes, bool a_AllowDynamicUpdate)
	: Buffer(1,GetAlignmentBytes(a_NumBytes),GraphicsObject::CONSTANT_BUFFER)
{
	m_Usage = (a_AllowDynamicUpdate ? GraphicsResource::Usage::DYNAMIC : GraphicsResource::Usage::IMMUTABLE);
}

Miracle::ConstantBuffer::~ConstantBuffer()
{

}

size_t Miracle::ConstantBuffer::GetAlignmentBytes(size_t a_NumBytes)
{
	if (a_NumBytes > 0)
	{
		size_t remainder = a_NumBytes % ALIGNMENT;
		if (remainder == 0)
		{
			return a_NumBytes;
		}
		else
		{
			return a_NumBytes + ALIGNMENT - remainder;
		}
	}
	else
	{
		return ALIGNMENT;
	}
}
