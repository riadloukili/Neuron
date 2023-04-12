#include "nrpch.h"
#include "Window.h"

#if defined(NR_PLATFORM_WINDOWS) || defined(NR_PLATFORM_LINUX) || defined(NR_PLATFORM_MACOS)

#include "Neuron/Platform/Desktop/DesktopWindow.h"

#endif

namespace Neuron {
    Scope<Window> Window::Create(const WindowProps &props) {
#if defined(NR_PLATFORM_WINDOWS) || defined(NR_PLATFORM_LINUX) || defined(NR_PLATFORM_MACOS)
        return CreateScope<DesktopWindow>(props);
#else
        NR_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
#endif
    }
}
