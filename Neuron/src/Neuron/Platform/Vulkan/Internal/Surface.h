#pragma once

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include "Instance.h"

namespace Neuron::Vulkan::Internal {

    class Surface {
    public:
        Surface(GLFWwindow *window, const Ref <Instance> &instance);

        ~Surface();

        const vk::SurfaceKHR &GetNative() { return m_Surface; }

    private:
        vk::SurfaceKHR m_Surface{nullptr};
        Ref <Instance> m_Instance;
    };

}
