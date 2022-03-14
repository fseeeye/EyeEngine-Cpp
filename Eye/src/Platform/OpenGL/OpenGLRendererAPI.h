#pragma once

#include "Eye/Renderer/RendererAPI.h"

namespace Eye {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const StrongRef<VertexArray>& vertexArray) override;
	};

}
