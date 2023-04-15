#pragma once

#include <vulkan/vulkan.hpp>
#include "PhysicalDevice.h"

namespace Neuron::Vulkan::Internal {

    class Device {
    public:
        explicit Device(const Ref <PhysicalDevice> &physicalDevice, const Ref <Surface> &surface, bool debug = false);

        ~Device();

        const vk::Device &GetNative() { return m_Device; }

    private:
        vk::Device m_Device;
        bool m_Debug;
    };

}