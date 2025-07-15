#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace GameEngine
{
	class GAMEENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

	private:

		std::unique_ptr<Window> _window;
		bool _running = true;
	};

	//To be defined in client.
	Application* CreateApplication();
}

