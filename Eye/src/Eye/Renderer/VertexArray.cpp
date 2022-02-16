#include "eyepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Eye {

	Eye::VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:   EYE_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
			default:                       EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

}