#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Eye {

	class Renderer
	{
	public:
		static void Init();

		/**
		 * @brief Set scene data: camera(VP matrix), lights, env, etc.
		 * 
		 * currently, it only sets VP matrix.
		 * @param orthoCamera camera for getting VP matrix.
		*/
		static void BeginScene(OrthographicCamera& orthoCamera);
		/**
		 * @brief Do sth. when stop setting scene data.
		 * 
		 * currently, it does nothing.
		*/
		static void EndScene();

		/**
		 * @brief Submit data to GPU & Request draw call
		 * 
		 * @param shader 
		 * @param vertexArray 
		 * @param transform 
		*/
		static void Submit(const StrongRef<Shader>& shader, const StrongRef<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));

		/**
		 * @brief Get render API which depends on current graphic backend.
		 * @return render API
		*/
		inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }

		static void OnWindowResize(uint32_t width, uint32_t height);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}
