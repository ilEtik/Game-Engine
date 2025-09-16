#include <GameEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Engine::Layer
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

		Engine::BufferLayout layout = {
			{ Engine::ShaderDataType::Float3, "a_position" },
			{ Engine::ShaderDataType::Float4, "a_color" }
		};

		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);

		Engine::Ref<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		_vertexArray.reset(Engine::VertexArray::Create());
		_vertexArray->AddVertexBuffer(vertexBuffer);
		_vertexArray->SetIndexBuffer(indexBuffer);

		_flatColorShader.reset(Engine::Shader::Create(flatColorVertexSource, flatColorFragmentSource));
	}

	virtual void OnUpdate(Engine::Timestep deltaTime) override
	{
		if (Engine::Input::IsKeyPressed(GE_KEY_W))
		{
			_cameraPosition.y += _cameraSpeed * deltaTime;
		}
		if (Engine::Input::IsKeyPressed(GE_KEY_A))
		{
			_cameraPosition.x -= _cameraSpeed * deltaTime;
		}
		if (Engine::Input::IsKeyPressed(GE_KEY_S))
		{
			_cameraPosition.y -= _cameraSpeed * deltaTime;
		}
		if (Engine::Input::IsKeyPressed(GE_KEY_D))
		{
			_cameraPosition.x += _cameraSpeed * deltaTime;
		}

		Engine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		Engine::RenderCommand::Clear();

		_camera.SetPosition(_cameraPosition);

		Engine::Renderer::BeginScene(_camera);

		std::dynamic_pointer_cast<Engine::OpenGLShader>(_flatColorShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(_flatColorShader)->UploadUniformFloat3("u_Color", _triangleColor);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Engine::Renderer::Submit(_flatColorShader, _vertexArray, transform);
			}
		}

		Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Triangle Color", glm::value_ptr(_triangleColor));
		ImGui::End();
	}

	void OnEvent(Engine::Event& event) override
	{
	}

private:
	Engine::Ref<Engine::Shader> _flatColorShader;
	Engine::Ref<Engine::VertexArray> _vertexArray;

	Engine::OrthographicCamera _camera;
	glm::vec3 _cameraPosition;
	float _cameraSpeed = 1.0f;

	glm::vec3 _triangleColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Engine::Application
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

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}