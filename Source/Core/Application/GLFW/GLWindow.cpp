#include <Core/Application/GLFW/GLWindow.h>
#include <Core/Event/GLFW/GLFWMessageLoop.h>
NAMESPACE_MENGINE_BEGIN

GLWindow::GLWindow()
{
	m_XOrigin = 0;
	m_YOrigin = 0;
	m_Width = 1280;
	m_Height = 720;
}


Miracle::GLWindow::GLWindow(_U32 a_Width, _U32 a_Height)
	: BaseWindow(a_Width,a_Height)
{
	m_XOrigin = 0;
	m_YOrigin = 0;
}

GLWindow::~GLWindow()
{
}

bool Miracle::GLWindow::Initialze()
{
	glfwInit();
	m_hWnd = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	if (m_hWnd == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(m_hWnd,GLFWMessageLoop::WindowSizeCallback);
	glfwSetKeyCallback(m_hWnd,GLFWMessageLoop::KeyCallback);
	glfwSetCharCallback(m_hWnd, GLFWMessageLoop::CharCallback);
	glfwSetScrollCallback(m_hWnd, GLFWMessageLoop::ScrollCallback);
	glfwSetCursorPosCallback(m_hWnd, GLFWMessageLoop::CursorPosCallback);
	glfwSetMouseButtonCallback(m_hWnd, GLFWMessageLoop::MouseButtonCallback);
	glfwSetWindowPosCallback(m_hWnd, GLFWMessageLoop::WindowPosCallback);
	glfwSetWindowCloseCallback(m_hWnd, GLFWMessageLoop::WindowCloseCallback);

	
	glfwMakeContextCurrent(m_hWnd);
	if (glewInit() != GLEW_OK)
	{
		return false;
	}
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	return true;
}

void GLWindow::SetTitle(const std::string& title)
{
	m_Title = title;
}

void GLWindow::OnIdle()
{

}

void GLWindow::OnDisplay()
{

}



NAMESPACE_MENGINE_END