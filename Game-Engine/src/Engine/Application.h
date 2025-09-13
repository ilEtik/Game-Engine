#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Engine/LayerStack.h"

#include "Engine/ImGui/ImGuiLayer.h"

namespace GameEngine
{
	class GAMEENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *_instance; }

		inline Window& GetWindow() { return *_window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

	private:
		static Application* _instance;

		std::unique_ptr<Window> _window;
		LayerStack _layerStack;

		bool _running = true;

		ImGuiLayer* _imGuiLayer;
	};

	//To be defined in client.
	Application* CreateApplication();
}

