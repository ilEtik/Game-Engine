#include "gepch.h"
#include "Application.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Log.h"

namespace GameEngine
{
	Application* Application::_instance = nullptr;

	Application::Application() 
		: _camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		_instance = this;

		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		uint32_t indices[3] = { 0, 1, 2 };

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_position;
				v_Color = a_color;
				gl_Position = u_ViewProjection * vec4(a_position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 _color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				_color = vec4(v_Position * 0.5, 1.0);
				_color = v_Color;
			}
		)";

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" }
		};
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		_vertexArray.reset(VertexArray::Create());
		_vertexArray->AddVertexBuffer(vertexBuffer);
		_vertexArray->SetIndexBuffer(indexBuffer);

		_shader.reset(new Shader(vertexSource, fragmentSource));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (_running)
		{
			RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1});
			RenderCommand::Clear();

			_camera.SetRotation(45.0f);

			Renderer::BeginScene(_camera);

			Renderer::Submit(_shader, _vertexArray);

			Renderer::EndScene();

			for (Layer* layer : _layerStack)
			{
				layer->OnUpdate();
			}

			// will be moved to render threat later
			_imGuiLayer->Begin();
			for (Layer* layer : _layerStack)
			{
				layer->OnImGuiRender();
			}
			_imGuiLayer->End();

			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		overlay->OnAttach();
		_layerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		_running = false;
		return true;
	}
}