#include <GameEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _cameraPosition(0.0f)
	{
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		uint32_t indices[3] = { 0, 1, 2 };

		std::string flatColorVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_position, 1.0);
			}
		)";

		std::string flatColorFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 _color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				_color = vec4(u_Color, 1.0);
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

		_flatColorShader.reset(GameEngine::Shader::Create(flatColorVertexSource, flatColorFragmentSource));
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

		GameEngine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		GameEngine::RenderCommand::Clear();

		_camera.SetPosition(_cameraPosition);

		GameEngine::Renderer::BeginScene(_camera);

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(_flatColorShader)->Bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(_flatColorShader)->UploadUniformFloat3("u_Color", _triangleColor);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				GameEngine::Renderer::Submit(_flatColorShader, _vertexArray, transform);
			}
		}

		GameEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Triangle Color", glm::value_ptr(_triangleColor));
		ImGui::End();
	}

	void OnEvent(GameEngine::Event& event) override
	{
	}

private:
	std::shared_ptr<GameEngine::Shader> _flatColorShader;
	std::shared_ptr<GameEngine::VertexArray> _vertexArray;

	GameEngine::OrthographicCamera _camera;
	glm::vec3 _cameraPosition;
	float _cameraSpeed = 1.0f;

	glm::vec3 _triangleColor = { 0.2f, 0.3f, 0.8f };
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