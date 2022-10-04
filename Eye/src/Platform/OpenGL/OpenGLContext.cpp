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
			reinterpret_cast<const char*>(glGetString(GL_VENDOR)), 
			reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
			reinterpret_cast<const char*>(glGetString(GL_VERSION))
		);

#ifdef EYE_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		EYE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Eye Engine requires OpenGL version 4.5 or later.");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
