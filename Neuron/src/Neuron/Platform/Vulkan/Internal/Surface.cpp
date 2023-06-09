#include "nrpch.h"
#include "Surface.h"

namespace Neuron::Vulkan::Internal {
    Surface::Surface(Window *window, const Ref <Instance> &instance)
            : m_Instance(instance) {
        NR_CORE_INFO("CREATING SURFACE");
        VkSurfaceKHR cStyleSurface;
        glfwCreateWindowSurface(m_Instance->GetNative(), (GLFWwindow *) window->GetNativeWindow(), nullptr,
                                &cStyleSurface);
        m_Surface = cStyleSurface;
    }

    Surface::~Surface() {
        NR_CORE_INFO("DELETING SURFACE");
        m_Instance->GetNative().destroySurfaceKHR(m_Surface, nullptr);
    }
}
