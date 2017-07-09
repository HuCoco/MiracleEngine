#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/Buffer.h>
#include <Rendering/Base/Resource/DataFormat.h>
#include <Rendering/Base/Resource/Buffer/VertexFormat.h>
NAMESPACE_MENGINE_BEGIN

class VertexBuffer : public Buffer
{
public:

	VertexBuffer(const VertexFormat& a_VertexFormat, _U32 a_NumVertices);
	virtual ~VertexBuffer();

	inline const VertexFormat& GetVertexFormat() const;
	inline bool StandardUsage() const;


private:

	VertexFormat m_VertexFormat;
};

inline const VertexFormat& VertexBuffer::GetVertexFormat() const
{
	return m_VertexFormat;
}

inline bool VertexBuffer::StandardUsage() const
{
	return true; // todo
}
NAMESPACE_MENGINE_END