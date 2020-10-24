#include "Application.h"

#include "Engine/Log.h"
#include "Events/ApplicationEvent.h"

namespace GameEngine
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		GE_TRACE(e);

		while (true)
		{

		}
	}
}