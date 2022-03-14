#pragma once

#include "Eye/Renderer/VertexArray.h"

namespace Eye {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const StrongRef<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const StrongRef<IndexBuffer>& indexBuffer) override;

		inline virtual const std::vector<StrongRef<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		inline virtual const StrongRef<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };
	private:
		uint32_t m_RendererID;
		std::vector<StrongRef<VertexBuffer>> m_VertexBuffers;
		StrongRef<IndexBuffer> m_IndexBuffer;
	};

}
