#pragma once

#include "PhysicalDevice.h"
#include "Surface.h"

namespace Neuron::Vulkan::Internal {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class Queues {
    public:
        static QueueFamilyIndices FindQueueFamilies(vk::PhysicalDevice &physicalDevice, Ref <Surface> &surface);
        static QueueFamilyIndices FindQueueFamilies(Ref <PhysicalDevice> &physicalDevice, Ref <Surface> &surface);
    };

}