#pragma once

#include "Core.h"

#include "Window.h"

#include "Eye/Events/Event.h"
#include "Eye/Events/KeyEvent.h"
#include "Eye/Events/MouseEvent.h"
#include "Eye/Events/ApplicationEvent.h"

#include "Eye/ImGui/ImGUiLayer.h"

#include "Eye/Renderer/Shader.h"
#include "Eye/Renderer/Buffer.h"
#include "Eye/Renderer/VertexArray.h"
#include "Eye/Renderer/OrthographicCamera.h"

#include "LayerStack.h"

namespace Eye {

	class EYE_API Application
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
		// Window Close Event Handler
		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_OrthoCamera;

	// singleton
	public:
		inline static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
