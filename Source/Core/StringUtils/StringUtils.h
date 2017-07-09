#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

static _U32 g_SeedTable[0x500];
static bool g_isInitialzedSeedTable = false;

class ME_EXPORT StringUtils
{
public:
	/* Split */
	static std::vector<std::string>& Split(const std::string& a_input, char a_delim, std::vector<std::string> &a_elems);
	static std::vector<std::string> Split(const std::string& a_input, char a_delim);

	/* char & w_char */
	static std::string ToAscii(const std::wstring& a_input);
	static std::wstring ToUnicode(const std::string& a_input);

	/* Format */
	static std::string Format(const char* format, ...);

	static _U32 ToHash(const std::string& a_name, _U32 a_seed);

	static std::string PointerToString(void* a_Address);

private:
	static char toupper(char a_ch);
	static void InitailzationSeedTable();
};

NAMESPACE_MENGINE_END