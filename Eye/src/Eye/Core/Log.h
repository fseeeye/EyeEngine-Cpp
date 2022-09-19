#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Eye {

	class EYE_API Log
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
#define EYE_CORE_TRACE(...) ::Eye::Log::GetCoreLogger()->trace(__VA_ARGS__) // explain: variadic macro
#define EYE_CORE_INFO(...)  ::Eye::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EYE_CORE_WARN(...)  ::Eye::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EYE_CORE_ERROR(...) ::Eye::Log::GetCoreLogger()->error(__VA_ARGS__) 
#define EYE_CORE_CRITICAL(...) ::Eye::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define EYE_TRACE(...) ::Eye::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EYE_INFO(...)  ::Eye::Log::GetClientLogger()->info(__VA_ARGS__)
#define EYE_WARN(...)  ::Eye::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EYE_ERROR(...) ::Eye::Log::GetClientLogger()->error(__VA_ARGS__) 
#define EYE_CRITICAL(...) ::Eye::Log::GetClientLogger()->critical(__VA_ARGS__)
