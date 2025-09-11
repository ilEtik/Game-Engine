#pragma once

namespace GameEngine
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return _rendererAPI; }
		static void SetAPI(RendererAPI rendererAPI);

	private:
		inline static RendererAPI _rendererAPI { RendererAPI::None };
	};
}