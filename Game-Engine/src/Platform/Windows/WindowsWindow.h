#pragma once

#include "Engine/Window.h"

#include <glfw/glfw3.h>

namespace GameEngine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return _data.Width; }
		inline unsigned int GetHeight() const override { return _data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);

	private:
		virtual void Shutdown();

	private:
		GLFWwindow* _window;

	public:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
	
		WindowData _data;
	};
}
