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
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// Bind Vertex Layout
		glEnableVertexAttribArray(0); // enable vertex attribute array 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // specify vertex attribute data layout & bind 

		// Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		// Vertex & Fragment Shaders
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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

			// Bind Shader
			m_Shader->Bind();

			// TEMP: draw a triangle
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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