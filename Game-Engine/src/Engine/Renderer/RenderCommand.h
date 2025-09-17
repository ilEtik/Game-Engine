#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Engine
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			_rendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			_rendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			_rendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			_rendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* _rendererAPI;
	};
}