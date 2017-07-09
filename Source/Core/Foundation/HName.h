#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class HName
{
public:
	HName();
	HName(const std::string& a_name);
	~HName();
	void Initialze(const std::string& a_name);
	inline bool IsInitialzed();
	inline std::string GetString() const;
	inline bool IsIpentity(const HName& a_other);
	inline HName& operator =	(const HName& a_other);
	inline bool operator ==(const HName& a_other) const;
	inline bool operator >=(const HName& a_other) const;
	inline bool operator <=(const HName& a_other) const;
	inline bool operator >	(const HName& a_other) const;
	inline bool operator >	(const HName* a_other) const;
	inline bool operator <	(const HName& a_other) const;
	inline bool operator !=(const HName& a_other) const;

private:
	bool m_IsInitialzed{ false };
	std::string m_Name{};
	_U32 m_MainValue{ 0 };
	_U32 m_CheckValue[2]{ 0,0 };
private:
	static _U8 Seed_1;
	static _U8 Seed_2;
	static _U8 Seed_3;
};

inline std::string HName::GetString() const
{
	return m_Name;
}

inline bool HName::IsInitialzed()
{
	return m_IsInitialzed;
}

bool Miracle::HName::IsIpentity(const HName& a_other)
{
	return (m_MainValue == a_other.m_MainValue &&
			m_CheckValue[0] == a_other.m_CheckValue[0] &&
			m_CheckValue[1] == a_other.m_CheckValue[1]);
}

inline HName& HName::operator=(const HName& a_other)
{
	this->m_IsInitialzed = a_other.m_IsInitialzed;
	this->m_MainValue = a_other.m_MainValue;
	this->m_CheckValue[0] = a_other.m_CheckValue[0];
	this->m_CheckValue[1] = a_other.m_CheckValue[1];
	this->m_Name = a_other.m_Name;
	return (*this);
}


inline bool HName::operator==(const HName& a_other) const
{
	return (this->m_MainValue == a_other.m_MainValue);
}

inline bool HName::operator>=(const HName& a_other) const
{	 
	return (this->m_MainValue >= a_other.m_MainValue);
}	 
	 
inline bool HName::operator<=(const HName& a_other) const
{
	return (this->m_MainValue <= a_other.m_MainValue);
}

inline bool HName::operator>(const HName& a_other) const
{
	return (this->m_MainValue > a_other.m_MainValue);
}

inline bool HName::operator>(const HName* a_other) const
{
	return (this->m_MainValue > a_other->m_MainValue);
}

inline bool HName::operator<(const HName& a_other) const
{
	return (this->m_MainValue < a_other.m_MainValue);
}

inline bool HName::operator!=(const HName& a_other) const
{
	return (this->m_MainValue != a_other.m_MainValue);
}


NAMESPACE_MENGINE_END