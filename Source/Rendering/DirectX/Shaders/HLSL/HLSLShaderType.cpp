#include "HLSLShaderType.h"



Miracle::HLSLShaderType::HLSLShaderType()
	: m_Name("")
{
}


Miracle::HLSLShaderType::~HLSLShaderType()
{
}

void Miracle::HLSLShaderType::SetDescription(D3D11_SHADER_TYPE_DESC const& a_Desc)
{
	m_Desc.VarClass = a_Desc.Class;
	m_Desc.VarType = a_Desc.Type;
	m_Desc.NumRows = a_Desc.Rows;
	m_Desc.NumColumns = a_Desc.Columns;
	m_Desc.NumElements = a_Desc.Elements;
	m_Desc.NumChildren = a_Desc.Members;
	m_Desc.Offset = a_Desc.Offset;
	m_Desc.TypeName = std::string(a_Desc.Name ? a_Desc.Name : "");

	if (a_Desc.Members > 0)
	{
		m_Children.resize(a_Desc.Members);
	}
	else
	{
		m_Children.clear();
	}
}

void Miracle::HLSLShaderType::SetName(std::string const& a_Name)
{
	m_Name = a_Name;
}

Miracle::HLSLShaderType& Miracle::HLSLShaderType::GetChild(_U32 a_Index)
{
	MENGINE_ASSERT_MSG(a_Index < m_Desc.NumChildren, "Invalid index.");
	return m_Children[a_Index];
}

Miracle::HLSLShaderType const& Miracle::HLSLShaderType::GetChild(_U32 a_Index) const
{
	MENGINE_ASSERT_MSG(a_Index < m_Desc.NumChildren, "Invalid index.");
	return m_Children[a_Index];
}

std::string const& Miracle::HLSLShaderType::GetName() const
{
	return m_Name;
}

D3D_SHADER_VARIABLE_CLASS Miracle::HLSLShaderType::GetClass() const
{
	return m_Desc.VarClass;
}

D3D_SHADER_VARIABLE_TYPE Miracle::HLSLShaderType::GetType() const
{
	return m_Desc.VarType;
}

_U32 Miracle::HLSLShaderType::GetNumRows() const
{
	return m_Desc.NumRows;
}

_U32 Miracle::HLSLShaderType::GetNumColumns() const
{
	return m_Desc.NumColumns;
}

_U32 Miracle::HLSLShaderType::GetNumElements() const
{
	return m_Desc.NumElements;
}

_U32 Miracle::HLSLShaderType::GetNumChildren() const
{
	return m_Desc.NumChildren;
}

_U32 Miracle::HLSLShaderType::GetOffset() const
{
	return m_Desc.Offset;
}

std::string const& Miracle::HLSLShaderType::GetTypeName() const
{
	return m_Desc.TypeName;
}

std::vector<Miracle::HLSLShaderType> const& Miracle::HLSLShaderType::GetChildren() const
{
	return m_Children;
}
