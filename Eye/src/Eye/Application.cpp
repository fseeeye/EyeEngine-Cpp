#include "eyepch.h"
#include "Application.h"

#include "Log.h"

#include<GLFW/glfw3.h>

namespace Eye {

#define BIND_EVENT_FN_1(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// create Window
		m_Window = std::unique_ptr<Window>(Window::Create());
		// set event callback function to Window
		m_Window->SetEventCallback(BIND_EVENT_FN_1(OnEvent));
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

	// Event callback func for Window, which dispatch event to handler func
	void Application::OnEvent(Event& e)
	{
		EYE_CORE_TRACE("Get Event: {}", e);
		// create EventDispatcher
		EventDispatcher dispatcher(e);

		// TODO: handle all events
		// check event type and dispatch it to correct func
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_1(OnWindowClosed)); // dispatch Window Closed Event
	}

	// Handle Window Closed Event
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

}