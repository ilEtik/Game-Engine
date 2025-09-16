#include "gepch.h"
#include "OpenGLContext.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: _windowHandle(windowHandle)
	{
		CORE_ASSERT(_windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{

		glfwMakeContextCurrent(_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Failed to initialize GLAD!");

		CORE_LOG_INFO("OpenGL Info:");
		CORE_LOG_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		CORE_LOG_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		CORE_LOG_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}
}