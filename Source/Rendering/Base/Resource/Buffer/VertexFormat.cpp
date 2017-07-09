#include "VertexFormat.h"


Miracle::VertexAttribute::VertexAttribute()
	: Semantic(VertexSemantic::NO_SEMANTIC)
	, Format(DataFormat::MENGINE_UNKNOWN)
	, Unit(0)
	, Offset(0)
{

}

Miracle::VertexFormat::VertexFormat()
	: m_ByteSize(0)
	, m_Attributes(0)
{

}

Miracle::VertexFormat::~VertexFormat()
{

}

void Miracle::VertexFormat::AddAttribute(VertexSemantic a_Semantic, DataFormat a_Format, _U32 Unit /*= 0*/)
{
	VertexAttribute Attribute;
	Attribute.Semantic = a_Semantic;
	Attribute.Format = a_Format;
	Attribute.Unit = 0;
	Attribute.Offset = m_ByteSize;

	m_Attributes.emplace_back(Attribute);
	m_ByteSize += DataFormatUtils::GetDataFormatBytes(a_Format);
}

Miracle::VertexSemantic Miracle::VertexFormat::GetSemantic(_U32 a_Index) const
{
	if (a_Index >= 0 && a_Index < m_Attributes.size())
	{
		return m_Attributes[a_Index].Semantic;
	}
	else
	{
		return NO_SEMANTIC;
	}
}

Miracle::DataFormat Miracle::VertexFormat::GetDataFormat(_U32 a_Index) const
{
	if (a_Index >= 0 && a_Index < m_Attributes.size())
	{
		return m_Attributes[a_Index].Format;
	}
	else
	{
		return DataFormat::MENGINE_UNKNOWN;
	}
}

_U32 Miracle::VertexFormat::GetUnit(_U32 a_Index) const
{
	if (a_Index >= 0 && a_Index < m_Attributes.size())
	{
		return m_Attributes[a_Index].Unit;
	}
	else
	{
		return 0;
	}
}

_U32 Miracle::VertexFormat::GetOffset(_U32 a_Index) const
{
	if (a_Index >= 0 && a_Index < m_Attributes.size())
	{
		return m_Attributes[a_Index].Offset;
	}
	else
	{
		return 0;
	}
}

_U32 Miracle::VertexFormat::GetByteSize() const
{
	return m_ByteSize;
}

_U32 Miracle::VertexFormat::GetNumAttributes() const
{
	return m_Attributes.size();
}
