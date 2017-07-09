#include <Rendering/Base/Resource/Buffer/IndexBuffer.h>
#include <Core/Mathematics/MathUtils.h>

_U32 Miracle::IndexBuffer::GetPolypointIndexCount(_U32 numPrimitives)
{
	// Create one point when numPrimitives is invalid.
	return numPrimitives > 0 ? numPrimitives : 1;
}

_U32 Miracle::IndexBuffer::GetPolysegmentDisjointIndexCount(
	_U32 numPrimitives)
{
	// Create one segment when numPrimitives is invalid.
	return numPrimitives > 0 ? 2 * numPrimitives : 2;
}

_U32 Miracle::IndexBuffer::GetPolysegmentContiguousIndexCount(
	_U32 numPrimitives)
{
	// Create one segment when numPrimitives is invalid.
	return numPrimitives > 0 ? numPrimitives + 1 : 2;
}

_U32 Miracle::IndexBuffer::GetTrimeshIndexCount(_U32 numPrimitives)
{
	// Create one triangle when numPrimitives is invalid.
	return numPrimitives > 0 ? 3 * numPrimitives : 3;
}

_U32 Miracle::IndexBuffer::GetTristripIndexCount(_U32 numPrimitives)
{
	// Create one triangle when numPrimitives is invalid.
	return numPrimitives > 0 ? numPrimitives + 2 : 3;
}

_U32 Miracle::IndexBuffer::GetPolysegmentDisjointAdjIndexCount(_U32 numPrimitives)
{
	// Create one segment-adj when numPrimitives is invalid.
	return numPrimitives > 0 ? 4 * numPrimitives : 4;
}

_U32 Miracle::IndexBuffer::GetPolysegmentContiguousAdjIndexCount(_U32 numPrimitives)
{
	// Create one segment-adj when numPrimitives is invalid.
	return numPrimitives > 0 ? numPrimitives + 3 : 4;
}

_U32 Miracle::IndexBuffer::GetTrimeshAdjIndexCount(_U32 numPrimitives)
{
	// Create one triangle-adj when numPrimitives is invalid.
	return numPrimitives > 0 ? 6 * numPrimitives : 6;
}

_U32 Miracle::IndexBuffer::GetTristripAdjIndexCount(_U32 numPrimitives)
{
	// Create one triangle-adj when numPrimitives is invalid.
	return numPrimitives > 0 ? 2 * (numPrimitives + 2) : 6;
}

Miracle::IndexBuffer::ICFunction Miracle::IndexBuffer::IndexCounter[NUM_TYPES] =
{
	&IndexBuffer::GetPolypointIndexCount,
	&IndexBuffer::GetPolysegmentDisjointIndexCount,
	&IndexBuffer::GetPolysegmentContiguousIndexCount,
	&IndexBuffer::GetTrimeshIndexCount,
	&IndexBuffer::GetTristripIndexCount,
	&IndexBuffer::GetPolysegmentDisjointAdjIndexCount,
	&IndexBuffer::GetPolysegmentContiguousAdjIndexCount,
	&IndexBuffer::GetTrimeshAdjIndexCount,
	&IndexBuffer::GetTristripAdjIndexCount
};

Miracle::IndexBuffer::IndexBuffer(PrimitiveType a_Type, _U32 a_NumPrimitives, size_t a_IndexSize)
	: Buffer(IndexCounter[MathUtils::Log2(a_Type)](a_NumPrimitives), a_IndexSize, GraphicsObject::INDEX_BUFFER)
	, m_PrimitiveType(a_Type)
	, m_NumPrimitives(a_NumPrimitives)
	, m_NumActivePrimitives(a_NumPrimitives)
{

}

Miracle::IndexBuffer::IndexBuffer(PrimitiveType a_Type, _U32 a_NumPrimitives)
	: Buffer(IndexCounter[MathUtils::Log2(a_Type)](a_NumPrimitives), 0, GraphicsObject::INDEX_BUFFER)
	, m_PrimitiveType(a_Type)
	, m_NumPrimitives(a_NumPrimitives)
	, m_NumActivePrimitives(a_NumPrimitives)
{

}

Miracle::IndexBuffer::~IndexBuffer()
{

}

void Miracle::IndexBuffer::SetNumActivePrimitives(_U32 a_NumActive)
{
	if (a_NumActive <= m_NumPrimitives)
	{
		m_NumActivePrimitives = a_NumActive;
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Invalid number of active primitives.");
		m_NumActivePrimitives = m_NumPrimitives;
	}
}

_U32 Miracle::IndexBuffer::GetNumActiveIndices() const
{
	_U32 i = MathUtils::Log2(m_PrimitiveType);
	return IndexCounter[i](m_NumActivePrimitives);
}
