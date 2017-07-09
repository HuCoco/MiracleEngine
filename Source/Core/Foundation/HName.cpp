#include <Core/Foundation/HName.h>
#include <Core/StringUtils/StringUtils.h>

NAMESPACE_MENGINE_BEGIN

_U8 HName::Seed_1 = 0;
_U8 HName::Seed_2 = 1;
_U8 HName::Seed_3 = 2;

HName::HName()
	: m_IsInitialzed(false)
	, m_Name("")
	, m_MainValue(0)
{
	memset(m_CheckValue, 0, sizeof(m_CheckValue));
}


HName::HName(const std::string& a_name)
{
	Initialze(a_name);
}

HName::~HName()
{
}

void HName::Initialze(const std::string& a_name)
{
	m_Name = a_name;
	m_MainValue = StringUtils::ToHash(m_Name, Seed_1);
	m_CheckValue[0] = StringUtils::ToHash(m_Name, Seed_2);
	m_CheckValue[1] = StringUtils::ToHash(m_Name, Seed_3);
	m_IsInitialzed = true;
}

NAMESPACE_MENGINE_END

