#include "gepch.h"
#include "Application.h"

#include "Engine/Log.h"

#include <GLFW/glfw3.h>

namespace GameEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (_running)
		{
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		GE_CORE_LOG_TRACE("{0}", event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		_running = false;
		return true;
	}
}