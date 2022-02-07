#include "eyepch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Eye {

	Eye::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		// decide which api to use
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::None:   EYE_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
			default:                  EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

	Eye::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		// decide which api to use
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::None:   EYE_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
			default:                  EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

}