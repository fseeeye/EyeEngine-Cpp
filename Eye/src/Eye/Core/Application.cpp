﻿#include "eyepch.h"
#include "Application.h"

#include "Eye/Core/Log.h"
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
		while (m_IsRunning)
		{
			// Calculate delta time
			float time = static_cast<float>(glfwGetTime()); // TODO: Platform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Udpate Layers
			if (!m_IsMinimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

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
		// Create EventDispatcher
		EventDispatcher dispatcher(e);

		// Check event type and dispatch it to correct func
		dispatcher.Dispatch<WindowCloseEvent>(EYE_BIND_EVENT_FN(Application::OnWindowClosed)); // dispatch Window Closed Event
		dispatcher.Dispatch<WindowResizeEvent>(EYE_BIND_EVENT_FN(Application::OnWindowResized)); // dispatch Window Resize Event

		// Boardcast event to layers if it
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

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_IsRunning = false;

		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e)
	{
		// Whether window is minimized
		if (e.GetWidth() == 0 && e.GetHeight() == 0) 
		{
			// We should tell application when window is minimized:
			// don't need to update layers anymore.
			m_IsMinimized = true; 

			return false;
		}
		m_IsMinimized = false;

		// Call renderer to perform resize operation : changing viewport
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false; // not block this envent
	}

}
