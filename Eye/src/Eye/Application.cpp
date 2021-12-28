#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Eye {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// Temp: test event
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			EYE_TRACE("Event Category - Application: {}", e);
		}

		while (true);
	}

}