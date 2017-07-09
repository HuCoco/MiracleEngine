#include <Core/Logging/MLogToFile.h>


Miracle::MLogToFile::MLogToFile(const std::string& a_FilePath, _U32 a_Flags)
	: MLogListener(a_Flags)
	, m_Filename(a_FilePath)
{
	std::ofstream logFile(m_Filename);
	if (logFile)
	{
		logFile.close();
	}
	else
	{
		m_Filename = "";
	}
}

Miracle::MLogToFile::~MLogToFile()
{
}

void Miracle::MLogToFile::Report(std::string const& a_Msg)
{
	if (m_Filename != "")
	{
		// Open for append.
		std::ofstream logFile(m_Filename,
			std::ios_base::out | std::ios_base::app);
		if (logFile)
		{
			logFile << a_Msg.c_str();
			logFile.close();
		}
		else
		{
			m_Filename = "";
		}
	}
}
