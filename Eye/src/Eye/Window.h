#pragma once

#include "eyepch.h"

#include "Eye/Core.h"
#include "Eye/Events/Event.h"

namespace Eye {

	// Window basic property
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Eye Engine",
						unsigned int width = 1280,
						unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	// Window Interface (Window virtual class) representing a desktop system based Window
	// tip: it will be impl for each platform
	class EYE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		// Window create function, which return system based Window
		static Window* Create(const WindowProps& props = WindowProps());

		// Window update stage
		virtual void OnUpdate() = 0;

		// Window Size
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
	
		// Window special attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		// Get internal window in any window instance
		virtual void* GetNativeWindow() const = 0;
	};

}

