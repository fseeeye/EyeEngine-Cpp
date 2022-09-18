#pragma once

#include "Eye/Renderer/RendererAPI.h"

namespace Eye {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const StrongRef<VertexArray>& vertexArray) override;
		virtual void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) override;
	};

}
