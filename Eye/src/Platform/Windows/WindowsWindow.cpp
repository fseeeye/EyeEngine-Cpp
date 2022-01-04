#include "eyepch.h"

#include "Eye/Events/KeyEvent.h"
#include "Eye/Events/MouseEvent.h"
#include "Eye/Events/ApplicationEvent.h"

#include "WindowsWindow.h"

#include <Glad/glad.h>

namespace Eye {
	
	// if we need to create multiple Window, we are not necessary to init glfw again.
	static bool s_GLFWInitialized = false;

	static void glfw_error_callback(int error, const char* description)
	{
		EYE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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

		// Init Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EYE_CORE_ASSERT(status, "Failed to initialize Glad!");

		// Set VSync
		SetVSync(m_Data.VSync);

		// used for GLFW callbacks to get event callback func
		glfwSetWindowUserPointer(m_Window, &m_Data);

		/* Set GLFW callbacks */ 
		// Window Resize Event
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			// Get WindowData pointer setting above
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			// Reset window Size data of current Window
			data.Width = width;
			data.Height = height;

			// Build Eye Engine Event type
			WindowResizeEvent event(width, height);
			// Call callback func
			data.EventCallback(event);
		});
		// Window Close Event
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		// Key Event
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// TODO: remapping keyboard int id
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
				}
			}
		});
		// Mouse Button Event
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		// Mouse Scroll Event
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xoffset, yoffset);
			data.EventCallback(event);
		});
		// Mouse Move Event
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xpos, ypos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}