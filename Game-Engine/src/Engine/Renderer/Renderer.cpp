#include "gepch.h"
#include "Renderer.h"

#include "Engine/Renderer/Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GameEngine
{
	void Renderer::SetAPI(RendererAPI rendererAPI)
	{
		_rendererAPI = rendererAPI;
	}
}