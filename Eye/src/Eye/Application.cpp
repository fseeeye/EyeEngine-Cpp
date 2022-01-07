#include "eyepch.h"
#include "Application.h"

#include "Log.h"

#include <Glad/gl.h>

namespace Eye {

#define BIND_EVENT_FN_1(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		// Create singleton of the Application class
		EYE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

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

			// Udpate Layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	// Event callback func for Window, which dispatch event to handler func
	void Application::OnEvent(Event& e)
	{
		//EYE_CORE_TRACE("Get Event: {}", e);
		// create EventDispatcher
		EventDispatcher dispatcher(e);

		// TODO: handle all events
		// check event type and dispatch it to correct func
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_1(OnWindowClosed)); // dispatch Window Closed Event

		if (!e.Handled) {
			// dispatch event into layers (from button to top)
			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
			{
				(*--it)->OnEvent(e);
				if (e.Handled)
					break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	// Handle Window Closed Event
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

}