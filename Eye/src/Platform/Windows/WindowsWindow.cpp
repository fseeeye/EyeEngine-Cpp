#include "eyepch.h"

#include "WindowsWindow.h"

namespace Eye {
	
	// if we need to create multiple Window, we are not necessary to init glfw again.
	static bool s_GLFWInitialized = false;

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
		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			// Enable vsync. 前后缓冲区交换间隔设置为1，即每绘制完成一桢才运行一次 glfwSwapBuffers(window) 来交换前后缓冲区;
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	static void glfw_error_callback(int error, const char* description)
	{
		// TODO: instead fprintf of EYE_CORE_ERROR
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EYE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			/* Initialize GLFW */
			// TODO: glfwTerminate on system shutdown
			glfwSetErrorCallback(glfw_error_callback);
			int success = glfwInit();
			EYE_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		EYE_CORE_ASSERT(m_Window, "Could not create Window!");

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		// used for event callback
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		SetVSync(m_Data.VSync);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}