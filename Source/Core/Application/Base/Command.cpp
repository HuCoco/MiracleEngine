#include <Core/Application/Base/Command.h>
#include <Core/StringUtils/StringUtils.h>

NAMESPACE_MENGINE_BEGIN

Command::Command()
{
	m_CommandList.clear();
}


Command::~Command()
{
	m_CommandList.clear();
}



void Command::AddCommand(const std::string& a_Command, _U64 a_FlagBit)
{
	m_CommandList.emplace_back(CommandGroup(a_Command,a_FlagBit));
}

void Miracle::Command::AddCommand(const CommandGroup* a_CommandGroup, _U32 a_Num)
{
	for (_U32 i = 0; i < a_Num; i++)
	{
		m_CommandList.emplace_back(a_CommandGroup[i]);
	}
}

void Miracle::Command::AddCommand(const CommandGroup& a_CommandGroup)
{
	m_CommandList.emplace_back(a_CommandGroup);
}

void Command::ProcessingCommand(const std::string& a_Command, char a_Split)
{
	std::vector<std::string> CommandArray = StringUtils::Split(a_Command, a_Split);
	for each (auto i in CommandArray)
	{
		for each (auto j in m_CommandList)
		{
			if (i == j.Command)
			{
				m_Flag |= j.FlagBit;
			}
		}
	}
}


NAMESPACE_MENGINE_END

bool Miracle::Command::IsThisCommand(_U64 a_FlagBit)
{
	if ((m_Flag & a_FlagBit) == a_FlagBit)
	{
		return true;
	}
	return false;
}
