#include <GameEngine.h>

#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _cameraPosition(0.0f), _trianglePosition(0.0f)
	{
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
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_position;
				v_Color = a_color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_position, 1.0);
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

		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_position" },
			{ GameEngine::ShaderDataType::Float4, "a_color" }
		};

		std::shared_ptr<GameEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GameEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);

		std::shared_ptr<GameEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(GameEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		_vertexArray.reset(GameEngine::VertexArray::Create());
		_vertexArray->AddVertexBuffer(vertexBuffer);
		_vertexArray->SetIndexBuffer(indexBuffer);

		_shader.reset(new GameEngine::Shader(vertexSource, fragmentSource));
	}

	virtual void OnUpdate(GameEngine::Timestep deltaTime) override
	{
		if (GameEngine::Input::IsKeyPressed(GE_KEY_W))
		{
			_cameraPosition.y += _cameraSpeed * deltaTime;
		}
		if (GameEngine::Input::IsKeyPressed(GE_KEY_A))
		{
			_cameraPosition.x -= _cameraSpeed * deltaTime;
		}
		if (GameEngine::Input::IsKeyPressed(GE_KEY_S))
		{
			_cameraPosition.y -= _cameraSpeed * deltaTime;
		}
		if (GameEngine::Input::IsKeyPressed(GE_KEY_D))
		{
			_cameraPosition.x += _cameraSpeed * deltaTime;
		}

		if (GameEngine::Input::IsKeyPressed(GE_KEY_I))
		{
			_trianglePosition.y += _triangleSpeed * deltaTime;
		}
		if (GameEngine::Input::IsKeyPressed(GE_KEY_J))
		{
			_trianglePosition.x -= _triangleSpeed * deltaTime;
		}
		if (GameEngine::Input::IsKeyPressed(GE_KEY_K))
		{
			_trianglePosition.y -= _triangleSpeed * deltaTime;
		}
		if (GameEngine::Input::IsKeyPressed(GE_KEY_L))
		{
			_trianglePosition.x += _triangleSpeed * deltaTime;
		}

		GameEngine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		GameEngine::RenderCommand::Clear();

		_camera.SetPosition(_cameraPosition);

		GameEngine::Renderer::BeginScene(_camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _trianglePosition);

		GameEngine::Renderer::Submit(_shader, _vertexArray, transform);

		GameEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(GameEngine::Event& event) override
	{
	}

private:
	std::shared_ptr<GameEngine::Shader> _shader;
	std::shared_ptr<GameEngine::VertexArray> _vertexArray;

	GameEngine::OrthographicCamera _camera;
	glm::vec3 _cameraPosition;
	float _cameraSpeed = 1.0f;

	glm::vec3 _trianglePosition;
	float _triangleSpeed = 0.5f;
};

class Sandbox : public GameEngine::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}