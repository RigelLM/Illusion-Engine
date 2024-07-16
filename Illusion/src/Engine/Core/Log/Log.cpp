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

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Two sinks with different log levels and formats.
	// The console will show only warnings or errors, while the file will log all.
	Ref<spdlog::sinks::stdout_color_sink_mt> s_ConsoleSink = CreateRef<spdlog::sinks::stdout_color_sink_mt>();
	Ref<spdlog::sinks::basic_file_sink_mt> s_FileSink = CreateRef<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);

	spdlog::logger Log::s_CoreLogger = spdlog::logger("ENGINE", { s_ConsoleSink , s_FileSink });
	spdlog::logger Log::s_ClientLogger = spdlog::logger("APP", { s_ConsoleSink , s_FileSink });

	void Log::Init()
	{
		s_ConsoleSink->set_level(spdlog::level::warn);
		s_ConsoleSink->set_pattern("%^[%T] %n: %v%$");

		s_FileSink->set_level(spdlog::level::trace);
		s_FileSink->set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger.set_level(spdlog::level::debug);
		s_ClientLogger.set_level(spdlog::level::debug);
	}
	//--------------------namespace: Illusion ends--------------------
}
