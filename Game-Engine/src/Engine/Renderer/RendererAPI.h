#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Engine/Renderer/VertexArray.h"

namespace GameEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return _api; }

	private:
		static API _api;
	};
}