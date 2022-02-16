#include "eyepch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Eye
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	// ref: https://github.com/gabime/spdlog#usage-samples
	void Log::Init()
	{	
		// set log pattern: [time] logger_name: text (all colored)
		// ref: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// create stdout logger object 
		s_CoreLogger = spdlog::stdout_color_mt("EYE");
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		// set log level
		s_CoreLogger->set_level(spdlog::level::trace); // set core log level to trace
		s_ClientLogger->set_level(spdlog::level::trace); // set client log level to trace
	}

}
