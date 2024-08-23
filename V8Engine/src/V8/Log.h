#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace V8
{
/// <summary>
/// Wrapper of spdlog
/// - https://github.com/gabime/spdlog
/// </summary>
class V8API Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
    {
        return s_CoreLogger;
    }

    inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
    {
        return s_ClientLogger;
    }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
} // namespace V8

#define V8_CORE_ERROR(...) ::V8::Log::GetCoreLogger()->error(__VA_ARGS__)
#define V8_CORE_WARN(...) ::V8::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define V8_CORE_INFO(...) ::V8::Log::GetCoreLogger()->info(__VA_ARGS__)
#define V8_CORE_DEBUG(...) ::V8::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define V8_CORE_TRACE(...) ::V8::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define CLI_ERROR(...) ::V8::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLI_WARN(...) ::V8::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLI_INFO(...) ::V8::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLI_DEBUG(...) ::V8::Log::GetClientLogger()->debug(__VA_ARGS__)
#define CLI_TRACE(...) ::V8::Log::GetClientLogger()->trace(__VA_ARGS__)