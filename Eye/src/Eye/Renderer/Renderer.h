#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Eye {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& orthoCamera);
		static void EndScene();

		static void Submit(const StrongRef<Shader>& shader, const StrongRef<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));

		inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}
