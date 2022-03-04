#include <Eye.h>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>


class ExampleLayer : public Eye::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_OrthoCamera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f)
	{
		// TEMP: draw a triangle
		// Vertex Array
		m_VertexArray.reset(Eye::VertexArray::Create());

		// Vertex Buffer
		float vertices[3 * 7] = {
			-0.5f, -0.37f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.37f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.37f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<Eye::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Eye::VertexBuffer::Create(vertices, sizeof(vertices)));

		// Vertex Layout
		Eye::BufferLayout layout = {
			{ Eye::ShaderDataType::Float3, "a_Position" },
			{ Eye::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Eye::IndexBuffer> indexBuffer;
		indexBuffer.reset(Eye::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		// TEMP: Draw Background Square
		m_SquareVA.reset(Eye::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};
		std::shared_ptr<Eye::VertexBuffer> squareVB;
		squareVB.reset(Eye::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({ { Eye::ShaderDataType::Float3, "a_Position" } });
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Eye::IndexBuffer> squareIB;
		squareIB.reset(Eye::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Vertex & Fragment Shaders
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = vec4(v_Color);
			}
		)";

		m_Shader.reset(new Eye::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Eye::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Eye::Timestep deltaTime) override
	{
		/* Handle Camera transform (View Matrix) */
		if (Eye::Input::IsKeyPressed(EYE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		else if (Eye::Input::IsKeyPressed(EYE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;

		if (Eye::Input::IsKeyPressed(EYE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		else if (Eye::Input::IsKeyPressed(EYE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;

		if (Eye::Input::IsKeyPressed(EYE_KEY_Q))
			m_CameraRotationAngle += m_CameraRotationSpeed * deltaTime;
		else if (Eye::Input::IsKeyPressed(EYE_KEY_E))
			m_CameraRotationAngle -= m_CameraRotationSpeed * deltaTime;

		m_OrthoCamera.SetPosition(m_CameraPosition);
		m_OrthoCamera.SetRotation(m_CameraRotationAngle);
		
		/* Draw */
		Eye::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.f });
		Eye::RenderCommand::Clear();

		Eye::Renderer::BeginScene(m_OrthoCamera);

		// First, draw a background square at below
		glm::mat4 transform;
		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.f);
				transform = glm::translate(glm::mat4(1.f), pos) * scale;

				Eye::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}
		// draw a triangle
		Eye::Renderer::Submit(m_Shader, m_VertexArray);

		Eye::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		
	}

	void OnEvent(Eye::Event& event) override
	{
		//Eye::EventDispatcher dispatcher(event);
	}

private:
	// Triangle
	std::shared_ptr<Eye::Shader> m_Shader;
	std::shared_ptr<Eye::VertexArray> m_VertexArray;

	// Background Square
	std::shared_ptr<Eye::Shader> m_BlueShader;
	std::shared_ptr<Eye::VertexArray> m_SquareVA;

	// Camera
	Eye::OrthographicCamera m_OrthoCamera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotationAngle = 0.f;
	float m_CameraMoveSpeed = 1.f;
	float m_CameraRotationSpeed = 60.f;
};

class Game : public Eye::Application
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
	}

	~Game()
	{

	}
};

Eye::Application* Eye::CreateApplication()
{
	return new Game();
}
