#include "Application.h"
#include "GLFW/glfw3.h"

#define  BIND_EVENT_FNC(x) std::bind(&Application::x,this,std::placeholders::_1)

Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallBack(BIND_EVENT_FNC(OnEvent));
}

Application::~Application()
{

}

void Application::Run()
{
	while (m_Running)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FNC(OnWindowClose));
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

int main()
{
	Application m_MusicPlayer;
	m_MusicPlayer.Run();
}