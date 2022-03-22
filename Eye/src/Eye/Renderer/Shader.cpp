#include "eyepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Eye {

	Eye::Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:   EYE_CORE_ASSERT(false, "`RendererAPI::None` is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
			default:                       EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

	Eye::Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:   EYE_CORE_ASSERT(false, "`RendererAPI::None` is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
		default:                       EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

}
