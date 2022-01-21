#include "eyepch.h"
#include "Application.h"

#include "Eye/Core.h"
#include "Eye/Log.h"
#include "Eye/Input.h"

#include <Glad/gl.h>

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

		// create ImGuiLayer and push over into LayerStack
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// TEMP: draw a triangle
		// Vertex Array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		// Vertex Buffer
		glGenBuffers(1, &m_VertexBuffer); // generate buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer); // bind buffer for sending data
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send data
		// Bind Vertex Layout
		glEnableVertexAttribArray(0); // enable vertex attribute array 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // specify vertex attribute data layout & bind 
		// Index Buffer
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			// TEMP: draw a triangle
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			// Udpate Layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Update ImGui
			// TODO: add to Render Thread
			m_ImGuiLayer->BeginImGuiRender();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->EndImGuiRender();

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