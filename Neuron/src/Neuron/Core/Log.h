#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Neuron {
    class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
            return s_CoreLogger;
        }

        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
            return s_ClientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define NR_CORE_TRACE(...) ::Neuron::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NR_CORE_INFO(...) ::Neuron::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NR_CORE_WARN(...) ::Neuron::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NR_CORE_ERROR(...) ::Neuron::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NR_CORE_FATAL(...) ::Neuron::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define NR_TRACE(...) ::Neuron::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NR_INFO(...) ::Neuron::Log::GetClientLogger()->info(__VA_ARGS__)
#define NR_WARN(...) ::Neuron::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NR_ERROR(...) ::Neuron::Log::GetClientLogger()->error(__VA_ARGS__)
#define NR_FATAL(...) ::Neuron::Log::GetClientLogger()->critical(__VA_ARGS__)