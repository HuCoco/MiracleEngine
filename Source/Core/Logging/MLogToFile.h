#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Logging/MLog.h>

NAMESPACE_MENGINE_BEGIN

class MLogToFile : public MLog::MLogListener
{
public:
	MLogToFile(const std::string& a_FilePath , _U32 a_Flags);
	~MLogToFile();

private:
	virtual void Report(std::string const& a_Msg) override;
	std::string m_Filename;
};

NAMESPACE_MENGINE_END