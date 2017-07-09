#include <Core/Logging/MLog.h>
#include <Core/StringUtils/StringUtils.h>

static MSet<Miracle::HName,Miracle::MLog::MLogListener*> s_Listeners;
static _U32 m_ErrorNumber = 0;
static _U32 m_WarningNumber = 0;
static _U32 m_InfomationNumber = 0;

Miracle::MLog::MLog(const char* a_File, const char* a_Function, _U32 a_Line, const std::string& a_Msg)
{
	m_Message =
		"[ File ] :" + std::string(a_File) + "\n" +
		"[ Func ] :" + std::string(a_Function) + "\n" +
		"[ Line ] :" + std::to_string(a_Line) + "\n" +
		a_Msg + "\n" +
		"===============================================\n";
		
}

Miracle::MLog::~MLog()
{

}

void Miracle::MLog::Error()
{
	MENGINE_SET_ITERATOR_BEGIN(s_Listeners)
	{
		
		if (MENGINE_SET_GET_VALUE->GetFlags() & MLogListener::LISTEN_FOR_ERROR)
		{
			MENGINE_SET_GET_VALUE->Error(m_Message);
		}
	}
	MENGINE_SET_ITERATOR_END(s_Listeners)
}

void Miracle::MLog::Warning()
{
	MENGINE_SET_ITERATOR_BEGIN(s_Listeners)
	{

		if (MENGINE_SET_GET_VALUE->GetFlags() & MLogListener::LISTEN_FOR_WARNING)
		{
			MENGINE_SET_GET_VALUE->Warning(m_Message);
		}
	}
	MENGINE_SET_ITERATOR_END(s_Listeners)
}

void Miracle::MLog::Information()
{
	MENGINE_SET_ITERATOR_BEGIN(s_Listeners)
	{

		if (MENGINE_SET_GET_VALUE->GetFlags() & MLogListener::LISTEN_FOR_INFORMATION)
		{
			MENGINE_SET_GET_VALUE->Information(m_Message);
		}
	}
	MENGINE_SET_ITERATOR_END(s_Listeners)
}

void Miracle::MLog::AddListener(MLogListener* a_Listener)
{
	s_Listeners.Insert(HName(StringUtils::PointerToString(a_Listener)),a_Listener);
}

void Miracle::MLog::RemoveListener(MLogListener* a_Listener)
{
	s_Listeners.Remove(HName(StringUtils::PointerToString(a_Listener)));
}

Miracle::MLog::MLogListener::MLogListener(_U32 a_Flags /*= LISTEN_FOR_NOTHING*/)
	: m_Flags(a_Flags)
{

}

Miracle::MLog::MLogListener::~MLogListener()
{

}

_U32 Miracle::MLog::MLogListener::GetFlags() const
{
	return m_Flags;
}

void Miracle::MLog::MLogListener::Error(const std::string& a_Msg)
{
	++m_ErrorNumber;
	Report("\n[ Error " + std::to_string(m_ErrorNumber) + "]\n" + a_Msg);
}

void Miracle::MLog::MLogListener::Warning(const std::string& a_Msg)
{
	++m_WarningNumber;
	Report("\n[ Warning " + std::to_string(m_WarningNumber) + "]\n" + a_Msg);
}

void Miracle::MLog::MLogListener::Information(const std::string& a_Msg)
{
	++m_InfomationNumber;
	Report("\n[ Infomation " + std::to_string(m_InfomationNumber) + "]\n" + a_Msg);
}

void Miracle::MLog::MLogListener::Report(std::string const& a_Msg)
{

}
