#pragma once
#include "window.h"
#include "GLFW/glfw3.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"


class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnUpdate() override;

	unsigned int GetWidth() const override { return m_Data.Width; }
	unsigned int GetHeight() const override { return m_Data.Height; }
	inline void SetEventCallBack(const EventCallBackFnc& callback) override { m_Data.EventCallBack = callback; }
	void SetVsync(bool enabled) override;
	bool IsVsync() const override;

private:
	virtual void Init(const WindowProps& props);
	virtual void Shutdown();

private:
	GLFWwindow* m_Window;
	struct WindowData
	{
		std::string title;
		unsigned int Width, Height;
		bool VSync;
		EventCallBackFnc EventCallBack;
	};
	WindowData m_Data;
};

