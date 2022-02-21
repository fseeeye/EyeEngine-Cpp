﻿#include "eyepch.h"
#include "Renderer.h"

namespace Eye {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& orthoCamera)
	{
		m_SceneData->ViewProjectionMatrix = orthoCamera.GetViewProjectionMatrix();
		// TODO: lights / environment
	}

	void Renderer::EndScene()
	{
		// TODO
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		// Shader set uniform
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		// Vertex Array Bind
		vertexArray->Bind();
		// Draw Call
		RenderCommand::DrawIndexed(vertexArray);
	}

}
