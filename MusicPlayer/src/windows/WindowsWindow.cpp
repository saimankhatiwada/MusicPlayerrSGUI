#include "WindowsWindow.h"

Window* Window::Create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
	Init(props);
}

WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Winodw);
}


void WindowsWindow::SetVsync(bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}
	m_Data.VSync = true;
}

bool WindowsWindow::IsVsync() const
{
	return m_Data.VSync;
}

void WindowsWindow::Init(const WindowProps& props)
{
	m_Data.title = props.Title;
	m_Data.Height = props.Height;
	m_Data.Width = props.Width;

	glfwInit();
	m_Winodw = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Winodw);
	glfwSetWindowUserPointer(m_Winodw, &m_Data);
	SetVsync(true);
}

void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(m_Winodw);
}
