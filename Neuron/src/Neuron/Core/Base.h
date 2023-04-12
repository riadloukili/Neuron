#pragma once

#include <memory>

#if defined(NR_PLATFORM_WINDOWS)
#define NR_DEBUGBREAK() __debugbreak()
#elif defined(NR_PLATFORM_LINUX) || defined(NR_PLATFORM_MACOS)

#include <csignal>

#define NR_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif

#define BIT(x) (1 << x)

#define NR_BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define NR_ASSERT(x, ...)                                   \
    {                                                       \
        if (!(x))                                           \
        {                                                   \
            NR_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            NR_DEBUGBREAK();                                \
        }                                                   \
    }
#define NR_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if (!(x))                                                \
        {                                                        \
            NR_CORE_FATAL("Assertion Failed: {0}", __VA_ARGS__); \
            NR_DEBUGBREAK();                                     \
        }                                                        \
    }


namespace Neuron {
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#include "Log.h"
