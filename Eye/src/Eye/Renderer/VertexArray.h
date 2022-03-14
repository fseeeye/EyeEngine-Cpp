#pragma once

#include <memory>

#include "Eye/Renderer/Buffer.h"

namespace Eye {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const StrongRef<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const StrongRef<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<StrongRef<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const StrongRef<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}
