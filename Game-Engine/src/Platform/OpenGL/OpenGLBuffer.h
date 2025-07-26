#pragma once

#include "Engine/Renderer/Buffer.h"

namespace GameEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t _rendererId;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return _count; }

	private:
		uint32_t _rendererId;

		uint32_t _count;
	};
}