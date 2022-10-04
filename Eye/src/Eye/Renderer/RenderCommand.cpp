#include "eyepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Eye {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = Scope<OpenGLRendererAPI>();

}
