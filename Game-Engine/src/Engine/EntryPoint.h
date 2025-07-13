#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{
	GameEngine::Log::Init();
	GE_CORE_LOG_WARN("Initialized Log!");
	GE_LOG_INFO("Initialized Log! Var = {0}", 23);
	GE_LOG_CRITICAL("THIS IS AN fatal message");

	GameEngine::Application* app = GameEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif