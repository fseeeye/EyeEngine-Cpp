#include "eyepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/gl.h>

namespace Eye {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		EYE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(m_WindowHandle);
		// Init Glad
		int version = gladLoadGL(glfwGetProcAddress);
		EYE_CORE_ASSERT(version, "Failed to initialize Glad!");
		
		EYE_CORE_INFO("OpenGL Info:\n\tVendor: {0}\n\tRenderer: {1}\n\tVersion: {2}", 
			glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}