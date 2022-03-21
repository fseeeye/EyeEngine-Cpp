#include "eyepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Eye {

	StrongRef<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:   EYE_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
			default:                       EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

}
