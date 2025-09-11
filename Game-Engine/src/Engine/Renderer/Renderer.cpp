#include "gepch.h"
#include "Renderer.h"

#include "Engine/Renderer/Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GameEngine
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}