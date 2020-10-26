#pragma once
#include "windows/window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include <memory>


class Application
{
public:
	Application();
	~Application();

	void Run();
	void OnEvent(Event& e);
private:
	bool OnWindowClose(WindowCloseEvent& e);
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};