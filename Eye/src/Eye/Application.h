#pragma once

#include "Core.h"

#include "Window.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "LayerStack.h"

namespace Eye {

	class EYE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		// Window Close Event Handler
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;

		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
