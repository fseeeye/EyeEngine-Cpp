#pragma once

#include "Core.h"

#include "Window.h"

#include "Eye/Events/Event.h"
#include "Eye/Events/KeyEvent.h"
#include "Eye/Events/MouseEvent.h"
#include "Eye/Events/ApplicationEvent.h"
#include "Eye/ImGui/ImGUiLayer.h"
#include "Eye/Core/LayerStack.h"

namespace Eye {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
		inline void PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

		inline Window& GetWindow() { return *m_Window; }
	private:
		/**
		 * @brief Handle window closed event
		 * 
		 * @param e event
		 * @return is successful
		*/
		bool OnWindowClosed(WindowCloseEvent& e);
		/**
		 * @brief Handle window resized event
		 * 
		 * When window resized event occurs, we should do:
		 * 1. Application handle the event: call renderer to change viewport.
		 * 2. notice application mainloop don't need to update layers anymore.
		 * 3. (optional) CameraController handle the event: chagne camera aspect ratio 
		 * which means change the projection matrix. So we'll see more/less scene info.
		 * @param e event
		 * @return is successful
		*/
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
		bool m_IsMinimized = false;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		float m_LastFrameTime;

	// singleton
	public:
		inline static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
