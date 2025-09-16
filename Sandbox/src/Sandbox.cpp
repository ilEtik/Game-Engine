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
		std::string flatColorVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_position, 1.0);
			}
		)";

		std::string flatColorFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 _color;

			uniform vec3 u_Color;

			void main()
			{
				_color = vec4(u_Color, 1.0);
			}
		)";

		_flatColorShader = Engine::Shader::Create(flatColorVertexSource, flatColorFragmentSource);

		std::string textureVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_position, 1.0);
			}
		)";

		std::string textureFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 _color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				_color = texture(u_Texture, v_TexCoord);
			}
		)";

		_textureShader = Engine::Shader::Create(textureVertexSource, textureFragmentSource);

		_texture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Engine::OpenGLShader>(_textureShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(_textureShader)->UploadUniformInt("u_Texture", 0);

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Engine::BufferLayout layout = {
			{ Engine::ShaderDataType::Float3, "a_position" },
			{ Engine::ShaderDataType::Float2, "a_TexCoord" },
		};

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);

		Engine::Ref<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		_squareVA.reset(Engine::VertexArray::Create());
		_squareVA->AddVertexBuffer(vertexBuffer);
		_squareVA->SetIndexBuffer(indexBuffer);

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
		std::dynamic_pointer_cast<Engine::OpenGLShader>(_flatColorShader)->UploadUniformFloat3("u_Color", _squareColor);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Engine::Renderer::Submit(_flatColorShader, _squareVA, transform);
			}
		}

		_texture->Bind();
		Engine::Renderer::Submit(_textureShader, _squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(_squareColor));
		ImGui::End();
	}

	void OnEvent(Engine::Event& event) override
	{
	}

private:
	Engine::Ref<Engine::Shader> _flatColorShader, _textureShader;
	Engine::Ref<Engine::VertexArray> _squareVA;

	Engine::Ref<Engine::Texture2D> _texture;

	Engine::OrthographicCamera _camera;
	glm::vec3 _cameraPosition;
	float _cameraSpeed = 1.0f;

	glm::vec3 _squareColor = { 0.2f, 0.3f, 0.8f };
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