#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Logging/MLog.h>

NAMESPACE_MENGINE_BEGIN

class MLogToOutputWindow : public MLog::MLogListener
{
public:
	MLogToOutputWindow(_U32 a_Flags);
	~MLogToOutputWindow();
private:
	virtual void Report(std::string const& a_Msg) override;
};

NAMESPACE_MENGINE_END