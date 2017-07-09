#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

#define CREATE_COMMAND_DATA(CommandArgs,Index) \
const Command::CommandGroup g_##CommandArgs##CommandGroup = Command::CommandGroup(#CommandArgs,1<<Index); 

#define CREATE_COMMAND_ARRAY_BEGIN						const static Command::CommandGroup g_CommandArgsList[] = {
#define CREATE_COMMAND_ARRAY_DATA(CommandArgs,Index)	Command::CommandGroup(CommandArgs,1<<Index)
#define CREATE_COMMAND_ARRAY_END						};



class Command
{
public:

	struct CommandGroup
	{
		std::string Command;
		_U64 FlagBit;

		CommandGroup(const std::string& a_Command, _U64 a_FlagBit)
			: Command(a_Command)
			, FlagBit(a_FlagBit)
		{

		}
	};

	Command();
	~Command();

	void AddCommand(const std::string& a_Command, _U64 a_FlagBit);
	void AddCommand(const CommandGroup& a_CommandGroup);
	void AddCommand(const CommandGroup* a_CommandGroup,_U32 a_Num);
	void ProcessingCommand(const std::string& a_Command, char a_Split);
	bool IsThisCommand(_U64 a_FlagBit);
private:




private:
	std::vector<CommandGroup> m_CommandList;
	_U64 m_Flag;
};

NAMESPACE_MENGINE_END