#include "gepch.h"
#include "Application.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Log.h"

#include <GLFW/glfw3.h>

namespace GameEngine
{
	Application* Application::_instance = nullptr;

	Application::Application()
	{
		_instance = this;

		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (_running)
		{
			float time = (float)glfwGetTime(); //TODO: Platform::GetTime()
			Timestep deltaTime = time - _lastFrameTime;
			_lastFrameTime = time;

			for (Layer* layer : _layerStack)
			{
				layer->OnUpdate(deltaTime);
			}

			// will be moved to render threat later
			_imGuiLayer->Begin();
			for (Layer* layer : _layerStack)
			{
				layer->OnImGuiRender();
			}
			_imGuiLayer->End();

			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		overlay->OnAttach();
		_layerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		_running = false;
		return true;
	}
}