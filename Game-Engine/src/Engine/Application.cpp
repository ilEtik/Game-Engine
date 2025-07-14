#include "gepch.h"
#include "Application.h"

#include "Engine/Log.h"
#include "Events/ApplicationEvent.h"

namespace GameEngine
{
	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (_running)
		{
			_window->OnUpdate();
		}
	}
}