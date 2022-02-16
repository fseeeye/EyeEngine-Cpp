#include "eyepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Eye {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}