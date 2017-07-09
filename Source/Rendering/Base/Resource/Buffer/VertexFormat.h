#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/DataFormat.h>
NAMESPACE_MENGINE_BEGIN

enum VertexSemantic
{
	NO_SEMANTIC,
	POSITION,
	BLENDWEIGHT,
	BLENDINDICES,
	NORMAL,
	PSIZE,
	TEXCOORD,
	TANGENT,
	BINORMAL,
	TESSFACTOR,
	POSITIONT,
	COLOR,
	FOG,
	DEPTH,
	SAMPLE,
	NUM_SEMANTICS,

	SEMANTIC_END
};

class VertexAttribute
{
public:
	VertexAttribute();
	~VertexAttribute() = default;
public:
	VertexSemantic Semantic;
	DataFormat Format;
	_U32 Unit;
	_U32 Offset;
};


class VertexFormat
{
public:
	VertexFormat();
	~VertexFormat();

	void AddAttribute(VertexSemantic a_Semantic, DataFormat a_Format, _U32 Unit = 0);

	VertexSemantic GetSemantic(_U32 a_Index) const;
	DataFormat GetDataFormat(_U32 a_Index) const;
	_U32 GetUnit(_U32 a_Index) const;
	_U32 GetOffset(_U32 a_Index) const;
	_U32 GetByteSize() const;
	_U32 GetNumAttributes() const;
private:
	_U32 m_ByteSize;
	std::vector<VertexAttribute> m_Attributes;
};

NAMESPACE_MENGINE_END