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

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		// TODO: set object position
		
		// Shader set uniform
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		// Vertex Array Bind
		vertexArray->Bind();
		// Draw Call
		RenderCommand::DrawIndexed(vertexArray);
	}

}
