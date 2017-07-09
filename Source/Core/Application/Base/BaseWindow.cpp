#include <Core/Application/Base/BaseWindow.h>

NAMESPACE_MENGINE_BEGIN

BaseWindow::BaseWindow()
{
}


Miracle::BaseWindow::BaseWindow(_U32 a_Width, _U32 a_Height)
	: m_Width(a_Width)
	, m_Height(a_Height)
{

}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::SetTitle(const std::string& a_title)
{
	m_Title = a_title;
}

void BaseWindow::OnMove(_I32 a_x, _I32 a_y)
{
	m_XOrigin = a_x;
	m_YOrigin = a_y;
}

bool BaseWindow::OnResize(_I32 a_width, _I32 a_height)
{
	m_IsMaximized = false;
	m_IsMinimized = false;

	if (m_Width != a_width || m_Height != a_width)
	{
		m_Width = a_width;
		m_Height = a_height;
		return true;
	}
	return false;
}

void BaseWindow::OnMinimize()
{
	m_IsMaximized = false;
	m_IsMinimized = true;
}

void BaseWindow::OnMaximize()
{
	m_IsMaximized = true;
	m_IsMinimized = false;
}

NAMESPACE_MENGINE_END