#pragma once

#include "Core.h"

namespace Eye {

	class EYE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run(); 
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
