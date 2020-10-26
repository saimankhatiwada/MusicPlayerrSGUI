#pragma once
#include "windows/window.h"

#include <memory>


class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	std::unique_ptr<Window> m_Window;
};