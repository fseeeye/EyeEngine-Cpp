#pragma once

#include "RenderCommand.h"

namespace Eye {

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
	};

}