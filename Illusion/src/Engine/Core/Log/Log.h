/*
 * ========================== Log.h ==========================
 *                          -- ils --
 *                                        CREATE -- 2023.01.12
 *                                        MODIFY --
 * ----------------------------------------------------------
 * Logging system
 * Recording data of the engine and game
 * ----------------------------
 */

#pragma once

#include "Engine/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	class Log
	{
	public:
		//Initialize the logging system
		//Set up loggers for both engine and application
		static void Init();

		inline static std::shared_ptr <spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr <spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

	private:
		//Two loggers: Logger for engine and logger for game application
		static std::shared_ptr <spdlog::logger> s_CoreLogger;
		static std::shared_ptr <spdlog::logger> s_ClientLogger;


	};
	//--------------------namespace: Illusion ends--------------------
}

//Core Log Macros
#define ENGINE_CORE_TRACE(...)			::Illusion::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)			::Illusion::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)			::Illusion::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)			::Illusion::Log::GetCoreLogger()->error(__VA_ARGS__)

//Client Log Macros								  
#define ENGINE_CLIENT_TRACE(...)		::Illusion::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_CLIENT_INFO(...)			::Illusion::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_CLIENT_WARN(...)			::Illusion::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_CLIENT_ERROR(...)		::Illusion::Log::GetClientLogger()->error(__VA_ARGS__)