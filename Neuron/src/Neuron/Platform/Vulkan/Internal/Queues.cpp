#include "nrpch.h"
#include "Queues.h"

namespace Neuron::Vulkan::Internal {

    QueueFamilyIndices Queues::FindQueueFamilies(const Ref <PhysicalDevice> &physicalDevice, const Ref <Surface> &surface) {
        auto device = physicalDevice->GetNative();
        return FindQueueFamilies(device, surface);
    }

    QueueFamilyIndices Queues::FindQueueFamilies(const vk::PhysicalDevice &physicalDevice, const Ref <Surface> &surface) {
        QueueFamilyIndices indices;

        // Getting all the queue families for a device
        std::vector<vk::QueueFamilyProperties> queueFamilies = physicalDevice.getQueueFamilyProperties();

        int i = 0;
        for (const auto &queueFamily: queueFamilies) {
            // Check if queue supports graphics.
            if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
            }
            // Check if queue supports presenting.
            // Note: Most queues that support graphics support presenting,
            //       we are making this check just to be absolutely sure.
            vk::Bool32 presentSupport = physicalDevice.getSurfaceSupportKHR(i, surface->GetNative());

            if (presentSupport) {
                indices.presentFamily = i;
            }
            // Only break when a graphics queue and a presenting queue are found.
            if (indices.isComplete()) {
                break;
            }
            i++;
        }

        NR_CORE_ASSERT(indices.isComplete(), "Couldn't find graphics queue or present queue!")

        return indices;
    }
}