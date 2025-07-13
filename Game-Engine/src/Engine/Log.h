#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace GameEngine
{
	class GAMEENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define GE_CORE_LOG_TRACE(...)		::GameEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_LOG_INFO(...)		::GameEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_LOG_WARN(...)		::GameEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_LOG_ERROR(...)		::GameEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_LOG_CRITICAL(...)	::GameEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GE_LOG_TRACE(...)			::GameEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GE_LOG_INFO(...)			::GameEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_LOG_WARN(...)			::GameEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_LOG_ERROR(...)			::GameEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_LOG_CRITICAL(...)		::GameEngine::Log::GetClientLogger()->critical(__VA_ARGS__)