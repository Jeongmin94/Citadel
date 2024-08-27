#include "Log.h"
#include "v8pch.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace V8
{
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init()
{
    // colorst - level with paading- timestamp - looger - msg - colorend
    spdlog::set_pattern("%^%=10l [%T] %n: %v%$");

    s_CoreLogger = spdlog::stdout_color_mt("V8");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);
}

void Log::Reset()
{
    s_CoreLogger.reset();
    s_ClientLogger.reset();
    spdlog::shutdown();
}

} // namespace V8