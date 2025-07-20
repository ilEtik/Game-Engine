#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (GameEngine::Input::IsKeyPressed(GE_KEY_TAB))
		{
			LOG_INFO("Tab Key is pressed!");
		}
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