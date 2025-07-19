#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
	}

	void OnEvent(GameEngine::Event& event) override
	{
	}
};

class Sandbox : public GameEngine::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new GameEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}