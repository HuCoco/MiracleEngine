#include <Core/Logging/MLogToOutputWindow.h>
#include <windows.h>

Miracle::MLogToOutputWindow::MLogToOutputWindow(_U32 a_Flags)
	: MLogListener(a_Flags)
{

}

Miracle::MLogToOutputWindow::~MLogToOutputWindow()
{
}

void Miracle::MLogToOutputWindow::Report(std::string const& a_Msg)
{
	std::wstring text(a_Msg.begin(), a_Msg.end());
	OutputDebugString(text.c_str());
}
