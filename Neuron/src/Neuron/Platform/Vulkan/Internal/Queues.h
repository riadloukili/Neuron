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
        static QueueFamilyIndices
        FindQueueFamilies(const vk::PhysicalDevice &physicalDevice, const Ref <Surface> &surface);

        static QueueFamilyIndices
        FindQueueFamilies(const Ref <PhysicalDevice> &physicalDevice, const Ref <Surface> &surface);

    public:
        inline static vk::Queue s_GraphicsQueue{nullptr};
        inline static vk::Queue s_PresentQueue{nullptr};
    };

}