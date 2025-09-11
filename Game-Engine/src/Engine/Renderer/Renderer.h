#pragma once

#include "Engine/Renderer/RendererAPI.h"
#include "Engine/Renderer/RenderCommand.h"

namespace GameEngine
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}