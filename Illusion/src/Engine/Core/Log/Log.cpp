/*
 * ========================== Log.h ==========================
 *                          -- ils --
 *                                        CREATE -- 2023.01.12
 *                                        MODIFY --
 * ----------------------------------------------------------
 * Logging system
 * Recording data of the engine and the game
 * ----------------------------
 */

#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	std::shared_ptr <spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr <spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		//Set up all the logging pattern
		spdlog::set_pattern("%^[%T] %n: %v%$");

		//Set up the Logger for game engine
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		//Set up Logger for game application
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
	//--------------------namespace: Illusion ends--------------------
}
