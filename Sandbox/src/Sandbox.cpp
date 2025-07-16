#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		LOG_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(GameEngine::Event& event) override
	{
		LOG_TRACE("{0}", event);
	}
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