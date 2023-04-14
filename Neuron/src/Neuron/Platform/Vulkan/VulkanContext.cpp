#include "nrpch.h"
#include "VulkanContext.h"

namespace Neuron::Vulkan {

    VulkanContext::VulkanContext(GLFWwindow *window) : m_Window(window) {}

    void VulkanContext::Init() {
#if defined(NR_DEBUG) || defined(NR_RELEASE)
        bool debug = true;
#else
        bool debug = false;
#endif
        m_Instance = CreateRef<Internal::Instance>("Neuron App", debug);
        m_Surface = CreateRef<Internal::Surface>(m_Window, m_Instance);
        m_GPU = CreateRef<Internal::PhysicalDevice>(m_Instance, m_Surface, debug);
    }

    void VulkanContext::SwapBuffers() {

    }

    VulkanContext::~VulkanContext() = default;


}
