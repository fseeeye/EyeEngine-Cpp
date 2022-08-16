#include "eyepch.h"
#include "Renderer.h"

// TMP
#include "Platform/OpenGL/OpenGLShader.h"

namespace Eye {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& orthoCamera)
	{
		s_SceneData->ViewProjectionMatrix = orthoCamera.GetViewProjectionMatrix();
		// TODO: lights / environment
	}

	void Renderer::EndScene()
	{
		// TODO
	}

	void Renderer::Submit(const StrongRef<Shader>& shader, const StrongRef<VertexArray>& vertexArray, const glm::mat4& transform /*= glm::mat4(1.f)*/)
	{
		// Shader set uniform
		shader->Bind();
		// TMP
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Model", transform);

		// TODO: Material System
		//mi.Bind();

		// Vertex Array Bind
		vertexArray->Bind();
		// Draw Call
		RenderCommand::DrawIndexed(vertexArray);
	}

}
