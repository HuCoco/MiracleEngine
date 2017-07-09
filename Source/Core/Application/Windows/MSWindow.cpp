#include <Core\Application\Windows\\MSWindow.h>
#include <Core\StringUtils\StringUtils.h>
#include <Core\Event\Windows\MSMessageLoop.h>
NAMESPACE_MENGINE_BEGIN

MSWindow::MSWindow() :
	m_Style(WS_OVERLAPPEDWINDOW | WS_VISIBLE)
{
	m_XOrigin = 0;
	m_YOrigin = 0;
	m_Width = 1280;
	m_Height = 720;
}


Miracle::MSWindow::MSWindow(_U32 a_Width, _U32 a_Height)
	: BaseWindow(a_Width,a_Height)
	, m_Style(WS_OVERLAPPEDWINDOW | WS_VISIBLE)
{
	m_XOrigin = 0;
	m_YOrigin = 0;
}

MSWindow::~MSWindow()
{
}


void Miracle::MSWindow::SetTitle(std::string const& title)
{
	BaseWindow::SetTitle(title);
	SetWindowText(m_hWnd, StringUtils::ToUnicode(title).c_str());
}

void Miracle::MSWindow::OnIdle()
{

}

void Miracle::MSWindow::OnDisplay()
{

}


bool Miracle::MSWindow::Initialze()
{
	WNDCLASSEX wc;

	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MSMessageLoop::MainEventLoop;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MiracleEngine";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	RECT rc;
	rc.top = rc.left = 0;
	rc.right = m_Width;
	rc.bottom = m_Height;

	AdjustWindowRectEx(&rc, m_Style, false, 0);

	_I32 lwidth = (rc.right - rc.left);
	_I32 lheight = (rc.bottom - rc.top);

	_I32 lleft = m_XOrigin;
	_I32 ltop = m_XOrigin;

	m_hWnd = CreateWindowEx(
		NULL,
		wc.lpszClassName,
		StringUtils::ToUnicode(m_Title).c_str(),
		m_Style,
		lleft, ltop,
		lwidth,
		lheight,
		NULL,
		NULL,
		NULL,
		NULL);

	RECT rect;
	GetClientRect(m_hWnd, &rect);
	m_Width = (rect.right - rect.left);
	m_Height = (rect.bottom - rect.top);

	if (m_hWnd) {
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		UpdateWindow(m_hWnd);
	}
	return true;
}


NAMESPACE_MENGINE_END