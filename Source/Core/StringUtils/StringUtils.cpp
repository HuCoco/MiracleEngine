#include "StringUtils.h"
#include <Core/Assert/AssertUtils.h>
#include <codecvt>
#include <stdarg.h>
NAMESPACE_MENGINE_BEGIN

std::vector<std::string>& StringUtils::Split(const std::string& a_input, char a_delim, std::vector<std::string> &a_elems)
{
	std::stringstream ss(a_input);
	std::string item;
	while (std::getline(ss, item, a_delim)) 
	{
		a_elems.push_back(item);
	}
	return a_elems;
}

std::vector<std::string> StringUtils::Split(const std::string& a_input, char a_delim)
{
	std::vector<std::string> elems;
	StringUtils::Split(a_input, a_delim, elems);
	return elems;
}


std::string StringUtils::ToAscii(const std::wstring& a_input)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(a_input);
}
//--------------------------------------------------------------------------------
std::wstring StringUtils::ToUnicode(const std::string& a_input)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(a_input);
}





std::string StringUtils::Format(const char* a_format, ...)
{
	va_list ap;
	va_start(ap, a_format);
	_I32 size = vsnprintf(nullptr, 0, a_format, ap) + 1;
	va_end(ap);
	char *buf = new char[size];
	va_start(ap, a_format);
	vsnprintf(buf, size, a_format, ap);
	va_end(ap);
	std::string fs(buf);
	delete[] buf;
	return fs;
}

_U32 StringUtils::ToHash(const std::string& a_name, _U32 a_seed)
{
	if (!g_isInitialzedSeedTable)
	{
		InitailzationSeedTable();
	}
	_U32 seed1 = 0x7FED7FED;
	_U32 seed2 = 0xEEEEEEEE;
	_I32 ch;
	for each(auto key in a_name)
	{
		ch = key;
		ch = toupper(ch);
		seed1 = g_SeedTable[(a_seed << 8) + ch] ^ (seed1 + seed2);
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
	}
	return seed1;
}

std::string Miracle::StringUtils::PointerToString(void* a_Address)
{
	return StringUtils::Format("%d", reinterpret_cast<intptr_t>(a_Address));
}

char StringUtils::toupper(char a_ch)
{
	return (a_ch >= 'a' && a_ch <= 'z') ? (a_ch ^ 0x20) : a_ch;
}

void StringUtils::InitailzationSeedTable()
{
	_U32 seed = 0x00100001;
	_U32 index1 = 0;
	_U32 index2 = 0;
	_U32 i;

	for (index1 = 0; index1 < 0x100; index1++)
	{
		for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
		{
			unsigned long temp1, temp2;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp1 = (seed & 0xFFFF) << 0x10;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp2 = (seed & 0xFFFF);
			g_SeedTable[index2] = (temp1 | temp2);
		}
	}

	g_isInitialzedSeedTable = true;
}

NAMESPACE_MENGINE_END