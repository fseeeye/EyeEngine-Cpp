#include "eyepch.h"
#include "Renderer.h"

namespace Eye {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& orthoCamera)
	{
		s_SceneData->ViewProjectionMatrix = orthoCamera.GetViewProjectionMatrix();
		// TODO: lights / environment
	}

	void Renderer::EndScene()
	{
		// TODOs
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform /*= glm::mat4(1.f)*/)
	{
		// Shader set uniform
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Model", transform);

		// Vertex Array Bind
		vertexArray->Bind();
		// Draw Call
		RenderCommand::DrawIndexed(vertexArray);
	}

}
