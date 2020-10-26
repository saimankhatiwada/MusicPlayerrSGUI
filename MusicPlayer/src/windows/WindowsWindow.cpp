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
	glfwSwapBuffers(m_Window);
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
	m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVsync(true);

	//set GLFW callback
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = Width;
			data.Height = Height;


			WindowResizeEvent eventWindowSize(Width, Height);
			data.EventCallBack(eventWindowSize);
		});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent eventWindowClose;
			data.EventCallBack(eventWindowClose);
		});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent eventKeyPress(key, 0);
				data.EventCallBack(eventKeyPress);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent eventKeyRelease(key);
				data.EventCallBack(eventKeyRelease);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent eventKeyPressedRepeat(key, 1);
				data.EventCallBack(eventKeyPressedRepeat);
				break;
			}
			}
		});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int KeyCode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(KeyCode);
			data.EventCallBack(event);
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent eventMouseButtonPress(button);
				data.EventCallBack(eventMouseButtonPress);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent eventMouseButtonRelease(button);
				data.EventCallBack(eventMouseButtonRelease);
				break;
			}
			}
		});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent eventMouseScroll((float)xOffset, (float)yOffset);
			data.EventCallBack(eventMouseScroll);
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent eventMouseCursorPos((float)xPos, (float)yPos);
			data.EventCallBack(eventMouseCursorPos);
		});
}

void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
}

