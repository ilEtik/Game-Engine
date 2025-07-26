#include "gepch.h"
#include "WindowsWindow.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

#include <glad/glad.h>

namespace GameEngine
{
	static bool _glfwInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	#pragma region GLFWCallbacks

	static void GLFWErrorCallback(int error_code, const char* description)
	{
		CORE_LOG_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	static void GLFWSetWindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	}

	static void GLFWSetWindowCloseCallback(GLFWwindow* window)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		data.EventCallback(event);
	}

	static void GLFWSetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
		}
	}

	static void GLFWSetCharCallback(GLFWwindow* window, unsigned int keycode)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keycode);
		data.EventCallback(event);
	}

	static void GLFWSetMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
		}
	}

	static void GLFWSetCharCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xoffset, (float)yoffset);
		data.EventCallback(event);
	}

	static void GLFWSetCursorPosCallback(GLFWwindow* window, double xPos, double yPos)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	}

	#pragma endregion

	void WindowsWindow::Init(const WindowProps& props)
	{
		_data.Title = props.Title;
		_data.Width = props.Width;
		_data.Height = props.Height;

		CORE_LOG_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!_glfwInitialized)
		{
			int success = glfwInit();
			CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			_glfwInitialized = true;
		}

		_window = glfwCreateWindow((int)props.Width, (int)props.Height, _data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Failed to initialize GLAD!");
		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(_window, GLFWSetWindowSizeCallback);
		glfwSetWindowCloseCallback(_window, GLFWSetWindowCloseCallback);
		glfwSetKeyCallback(_window, GLFWSetKeyCallback);
		glfwSetCharCallback(_window, GLFWSetCharCallback);
		glfwSetMouseButtonCallback(_window, GLFWSetMouseButtonCallback);
		glfwSetScrollCallback(_window, GLFWSetCharCallback);
		glfwSetCursorPosCallback(_window, GLFWSetCursorPosCallback);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return _data.VSync;
	}
}