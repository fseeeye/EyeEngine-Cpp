﻿#include "eyepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Eye {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Eye::ShaderDataType::Float:  return GL_FLOAT;
			case Eye::ShaderDataType::Float2: return GL_FLOAT;
			case Eye::ShaderDataType::Float3: return GL_FLOAT;
			case Eye::ShaderDataType::Float4: return GL_FLOAT;
			case Eye::ShaderDataType::Mat3:   return GL_FLOAT;
			case Eye::ShaderDataType::Mat4:   return GL_FLOAT;
			case Eye::ShaderDataType::Int:    return GL_INT;
			case Eye::ShaderDataType::Int2:   return GL_INT;
			case Eye::ShaderDataType::Int3:   return GL_INT;
			case Eye::ShaderDataType::Int4:   return GL_INT;
			case Eye::ShaderDataType::Bool:   return GL_BOOL;
		}

		EYE_CORE_ASSERT(false, "Unknow Shader Data Type!");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
		m_RendererID = 0;
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		EYE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has nolayout!");

		m_VertexBuffers.push_back(vertexBuffer);

		// make sure the Vertex Array & Vertex Buffer have been bind
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		// Tie Vertex Buffer and its Layout to Vertex Array
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index); // enable vertex attribute array 0
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset); // specify vertex attribute data layout & bind
			++index;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;

		// make sure the Vertex Array & Vertex Buffer have been bind
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		// btw: that's it... OpenGL is such a garbage...
	}

}