#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <Core/Foundation/HName.h>
NAMESPACE_MENGINE_BEGIN

class MLog
{
public:
	MLog(const char* a_File,const char* a_Function,_U32 a_Line, const std::string& a_Msg);
	~MLog();
	void Error();
	void Warning();
	void Information();

	class MLogListener
	{
	public:
		enum
		{
			LISTEN_FOR_NOTHING = 0x00000000,
			LISTEN_FOR_ERROR = 0x00000001,
			LISTEN_FOR_WARNING = 0x00000002,
			LISTEN_FOR_INFORMATION = 0x00000004,
			LISTEN_FOR_ALL = 0xFFFFFFFF
		};

		virtual ~MLogListener();
		MLogListener(_U32 a_Flags = LISTEN_FOR_NOTHING);

		_U32 GetFlags() const;

		void Error(const std::string& a_Msg);
		void Warning(const std::string& a_Msg);
		void Information(const std::string& a_Msg);

	private:
		virtual void Report(std::string const& a_Msg);
		_U32 m_Flags;
	};

	static void AddListener(MLogListener* a_Listener);
	static void RemoveListener(MLogListener* a_Listener);

private:
	std::string m_Message;
};

#if !defined(NO_LOGGER)

#define MENGINE_LOG_ASSERT(condition, message) \
    if (!(condition)) \
    { \
        Miracle::MLog(__FILE__, __FUNCTION__, __LINE__, message).Assertion(); \
    }

#define MENGINE_LOG_ERROR(message) \
   Miracle::MLog(__FILE__, __FUNCTION__, __LINE__, message).Error()

#define MENGINE_LOG_WARNING(message) \
   Miracle::MLog(__FILE__, __FUNCTION__, __LINE__, message).Warning()

#define MENGINE_LOG_INFORMATION(message) \
    Miracle::MLog(__FILE__, __FUNCTION__, __LINE__, message).Information()

#else

// No logging of assertions, warnings, errors, or information.
#define MENGINE_LOG_ASSERT(condition, message)
#define MENGINE_LOG_ERROR(message)
#define MENGINE_LOG_WARNING(message)
#define MENGINE_LOG_INFORMATION(message)

#endif


NAMESPACE_MENGINE_END