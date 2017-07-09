#include <Core\Foundation\HObject.h>


Miracle::HObject::HObject(HObjectType a_Type)
	: m_Name()
	, m_Type(a_Type)
{

}


Miracle::HObject::HObject(HObjectType a_Type, const std::string& a_Name)
	: m_Name(a_Name)
	, m_Type(a_Type)
{

}

Miracle::HObject::~HObject()
{
}

void Miracle::HObject::SetName(const std::string& a_Name)
{
	m_Name.Initialze(a_Name);
}

void Miracle::HObject::SetName(const HName& a_Name)
{
	m_Name = a_Name;
}
