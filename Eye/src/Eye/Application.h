#pragma once

#include "Core.h"

#include "Window.h"

#include "Eye/Events/Event.h"
#include "Eye/Events/KeyEvent.h"
#include "Eye/Events/MouseEvent.h"
#include "Eye/Events/ApplicationEvent.h"

#include "Eye/ImGui/ImGUiLayer.h"

#include "Eye/Renderer/Shader.h"

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

		inline Window& GetWindow() { return *m_Window; }
	private:
		// Window Close Event Handler
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	// singleton
	public:
		inline static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
