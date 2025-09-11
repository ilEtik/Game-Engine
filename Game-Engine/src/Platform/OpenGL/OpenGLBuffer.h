#pragma once

#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Renderer.h"

namespace GameEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { _layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return _layout; }

	private:
		uint32_t _rendererId;
		BufferLayout _layout;
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