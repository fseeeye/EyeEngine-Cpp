#include "eyepch.h"
#include "Application.h"

#include "Eye/Core.h"
#include "Eye/Log.h"
#include "Eye/Input.h"
#include "Eye/Core/Timestep.h"
#include "Eye/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Eye {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		// Create singleton of the Application class
		EYE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// create Window
		m_Window = std::unique_ptr<Window>(Window::Create());
		// set event callback function to Window
		m_Window->SetEventCallback(EYE_BIND_EVENT_FN(Application::OnEvent));

		m_Window->SetVSync(true);

		Renderer::Init();

		// create ImGuiLayer and push over into LayerStack
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Calculate delta time
			float time = static_cast<float>(glfwGetTime()); // TODO: Platform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Udpate Layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			// Update ImGui
			// TODO: add to Render Thread
			m_ImGuiLayer->BeginImGuiRender();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->EndImGuiRender();

			// Update glfw Window
			m_Window->OnUpdate();
		}
	}

	// Event callback func for Window, which dispatch event to handler func
	void Application::OnEvent(Event& e)
	{
		//EYE_CORE_TRACE("Get Event: {}", e);
		// create EventDispatcher
		EventDispatcher dispatcher(e);

		// check event type and dispatch it to correct func
		dispatcher.Dispatch<WindowCloseEvent>(EYE_BIND_EVENT_FN(Application::OnWindowClosed)); // dispatch Window Closed Event

		// boardcast event to layers
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

	// Handle Window Closed Event
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

}
