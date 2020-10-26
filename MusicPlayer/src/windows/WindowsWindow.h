#pragma once
#include "window.h"
#include "GLFW/glfw3.h"


class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnUpdate() override;

	unsigned int GetWidth() const override { return m_Data.Width; }
	unsigned int GetHeight() const override { return m_Data.Height; }
	void SetVsync(bool enabled) override;
	bool IsVsync() const override;

private:
	virtual void Init(const WindowProps& props);
	virtual void Shutdown();

private:
	GLFWwindow* m_Winodw;
	struct WindowData
	{
		std::string title;
		unsigned int Width, Height;
		bool VSync;
	};
	WindowData m_Data;
};

