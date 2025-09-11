#include "gepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GameEngine
{
	RendererAPI* RenderCommand::_rendererAPI = new OpenGLRendererAPI();
}