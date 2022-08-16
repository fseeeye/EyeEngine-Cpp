#include <Eye.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Eye::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_OrthoCameraController(1280.f / 720.f)
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
		Eye::StrongRef<Eye::VertexBuffer> vertexBuffer;
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
		Eye::StrongRef<Eye::IndexBuffer> indexBuffer;
		indexBuffer.reset(Eye::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		// TEMP: Draw Background Square
		m_SquareVA.reset(Eye::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		}; // vertex(3) + texture coord(2)
		Eye::StrongRef<Eye::VertexBuffer> squareVB;
		squareVB.reset(Eye::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({ 
			{ Eye::ShaderDataType::Float3, "a_Position" },
			{ Eye::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Eye::StrongRef<Eye::IndexBuffer> squareIB;
		squareIB.reset(Eye::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Vertex & Fragment Shaders
		// vertex position color shader
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
				color = v_Color;
			}
		)";

		m_Shader = Eye::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		// flat color shader
		std::string flatShaderVertexSrc = R"(
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

		std::string flatShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatShader = Eye::Shader::Create("FlatColor", flatShaderVertexSrc, flatShaderFragmentSrc);

		// texture shader
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		//auto textureShader = Renderer::GetShaderLibrary()->Load("assets/shaders/Texture.glsl"); // TODO

		// Create & Upload Texture
		m_Texture = Eye::Texture2D::Create("assets/textures/Checkerboard_RGB.png");
		m_ChernoLogoTexture = Eye::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Eye::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Eye::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Eye::Timestep deltaTime) override
	{
		/* Update */
		m_OrthoCameraController.OnUpdate(deltaTime);
		
		/* Render */
		Eye::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.f });
		Eye::RenderCommand::Clear();

		Eye::Renderer::BeginScene(m_OrthoCameraController.GetCamera());

		// TODO: Render 2D
		//Eye::Renderer2D::BeginScene(m_Scene);

		// 1. Draw example background squares at below
		std::dynamic_pointer_cast<Eye::OpenGLShader>(m_FlatShader)->Bind();
		std::dynamic_pointer_cast<Eye::OpenGLShader>(m_FlatShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		// TODO: Material System
		//Eye::MaterialRef material = new Eye::Matrial(m_FlatShader);
		//Eye::MaterialInstanceRef mi = new Eye::MatrialInstance(material);
		//mi->SetValue("u_Color", redColor);
		//mi->SetTexture("u_AlbedoMap", texture);
		//squareMesh->SetMaterial(mi);

		glm::mat4 transform;
		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				// calc transform
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.f);
				transform = glm::translate(glm::mat4(1.f), pos) * scale;

				Eye::Renderer::Submit(m_FlatShader, m_SquareVA, transform);
				// TODO: Material System
				//Eye::Renderer::Submit(mi, m_SquareVA, transform);
			}
		}

		// 2. Draw for testing Texture
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Eye::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		Eye::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
		 
		// 3. Draw a triangle
		//Eye::Renderer::Submit(m_Shader, m_VertexArray);

		Eye::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Eye::Event& event) override
	{
		m_OrthoCameraController.OnEvent(event);
	}

private:
	// Triangle
	Eye::ShaderLibrary m_ShaderLibrary;
	Eye::StrongRef<Eye::Shader> m_Shader;
	Eye::StrongRef<Eye::VertexArray> m_VertexArray;

	// Background Square
	Eye::StrongRef<Eye::Shader> m_FlatShader;
	Eye::StrongRef<Eye::VertexArray> m_SquareVA;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	Eye::StrongRef<Eye::Texture2D> m_Texture, m_ChernoLogoTexture;

	// Camera
	Eye::OrthographicCameraController m_OrthoCameraController;
};

class Game : public Eye::Application
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
	}

	~Game() = default;
};

Eye::Application* Eye::CreateApplication()
{
	return new Game();
}
