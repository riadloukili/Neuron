#pragma once

#include <vulkan/vulkan.hpp>
#include "PhysicalDevice.h"

namespace Neuron::Vulkan::Internal {

    class Device {
    public:
        explicit Device(Ref <PhysicalDevice> &physicalDevice, Ref <Surface> &surface, bool debug = false);

        ~Device();

        vk::Device GetNative() { return m_Device; }

    private:
        Ref <PhysicalDevice> &m_GPU;
        vk::Device m_Device;
        bool m_Debug;
    };

}