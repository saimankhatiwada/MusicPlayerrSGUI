#pragma once
#include <string>

struct WindowProps
{
	std::string Title;
	unsigned int Width, Height;
	WindowProps(const std::string title = "MusicPlayer", unsigned int width = 1280, unsigned int height = 720)
		:Title(title), Width(width), Height(height)
	{

	}
};

class Window
{
public:
	virtual ~Window() {}
	virtual void OnUpdate() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual void SetVsync(bool enabled) = 0;
	virtual bool IsVsync() const = 0;

	static Window* Create(const WindowProps& props = WindowProps());
};