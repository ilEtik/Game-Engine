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

		virtual void OnUpdate() override;

		inline virtual unsigned int GetWidth() const override { return _data.Width; }
		inline virtual unsigned int GetHeight() const override { return _data.Height; }

		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return _window; }

	private:
		virtual void Init(const WindowProps& props);
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
