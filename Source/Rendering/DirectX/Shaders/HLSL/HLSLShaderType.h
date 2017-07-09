#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class HLSLShaderType
{
public:
	struct Description
	{
		D3D_SHADER_VARIABLE_CLASS VarClass;
		D3D_SHADER_VARIABLE_TYPE VarType;
		_U32 NumRows;
		_U32 NumColumns;
		_U32 NumElements;
		_U32 NumChildren;
		_U32 Offset;
		std::string TypeName;
	};

	HLSLShaderType();
	~HLSLShaderType();

	void SetDescription(D3D11_SHADER_TYPE_DESC const& a_Desc);
	void SetName(std::string const& a_Name);

	HLSLShaderType& GetChild(_U32 a_Index);
	HLSLShaderType const& GetChild(_U32 a_Index) const;

	std::string const& GetName() const;
	D3D_SHADER_VARIABLE_CLASS GetClass() const;
	D3D_SHADER_VARIABLE_TYPE GetType() const;
	_U32 GetNumRows() const;
	_U32 GetNumColumns() const;
	_U32 GetNumElements() const;
	_U32 GetNumChildren() const;
	_U32 GetOffset() const;
	std::string const& GetTypeName() const;
	std::vector<HLSLShaderType> const& GetChildren() const;

private:
	Description m_Desc;
	std::string m_Name;
	std::vector<HLSLShaderType> m_Children;
};

NAMESPACE_MENGINE_END