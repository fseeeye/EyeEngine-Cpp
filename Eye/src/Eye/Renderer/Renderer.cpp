#include "eyepch.h"
#include "Renderer.h"

namespace Eye {

	void Renderer::BeginScene()
	{
		// TODO
	}

	void Renderer::EndScene()
	{
		// TODO
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
