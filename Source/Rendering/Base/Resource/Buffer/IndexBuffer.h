#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/DataFormat.h>
#include <Rendering/Base/Resource/Buffer/Buffer.h>

NAMESPACE_MENGINE_BEGIN

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(PrimitiveType a_Type, _U32 a_NumPrimitives,size_t a_IndexSize);
	IndexBuffer(PrimitiveType a_Type, _U32 a_NumPrimitives);
	virtual ~IndexBuffer();

	inline PrimitiveType GetPrimitiveType();
	inline _U32 GetNumPrimitives() const;
	inline bool IsIndexed() const;

	void SetNumActivePrimitives(_U32 a_NumActive);
	inline _U32 GetNumActivePrimitives() const;
	_U32 GetNumActiveIndices() const;

protected:
	typedef _U32(*ICFunction)(_U32);
	static ICFunction IndexCounter[PrimitiveType::NUM_TYPES];

	static _U32 GetPolypointIndexCount(_U32 numPrimitives);
	static _U32 GetPolysegmentDisjointIndexCount(_U32 numPrimitives);
	static _U32 GetPolysegmentContiguousIndexCount(_U32 numPrimitives);
	static _U32 GetTrimeshIndexCount(_U32 numPrimitives);
	static _U32 GetTristripIndexCount(_U32 numPrimitives);
	static _U32 GetPolysegmentDisjointAdjIndexCount(_U32 numPrimitives);
	static _U32 GetPolysegmentContiguousAdjIndexCount(_U32 numPrimitives);
	static _U32 GetTrimeshAdjIndexCount(_U32 numPrimitives);
	static _U32 GetTristripAdjIndexCount(_U32 numPrimitives);

private:
	PrimitiveType m_PrimitiveType;
	_U32 m_NumPrimitives;
	_U32 m_NumActivePrimitives;
};

inline PrimitiveType IndexBuffer::GetPrimitiveType()
{
	return m_PrimitiveType;
}

inline _U32 IndexBuffer::GetNumPrimitives() const
{
	return m_NumPrimitives;
}

inline bool IndexBuffer::IsIndexed() const
{
	return m_pData != nullptr;
}

inline _U32 IndexBuffer::GetNumActivePrimitives() const
{
	return m_NumActivePrimitives;
}



NAMESPACE_MENGINE_END