#include "nrpch.h"
#include "Device.h"
#include "Queues.h"
#include "Debug.h"

namespace Neuron::Vulkan::Internal {
    Device::Device(const Ref <PhysicalDevice> &physicalDevice, const Ref <Surface> &surface, bool debug)
            : m_GPU(physicalDevice), m_Debug(debug) {

        NR_CORE_INFO("CREATING LOGICAL DEVICE");

        QueueFamilyIndices indices = Queues::FindQueueFamilies(m_GPU, surface);

        // In case the queue families are the same, we only get one.
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        // Device queues creation, creates for graphics family and present family.
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        float queuePriority = 1.0f;
        for (uint32_t queueFamily: uniqueQueueFamilies) {
            vk::DeviceQueueCreateInfo queueCreateInfo = vk::DeviceQueueCreateInfo(
                    vk::DeviceQueueCreateFlags(),
                    queueFamily,
                    1,
                    &queuePriority
            );
            queueCreateInfos.push_back(queueCreateInfo);
        }

        // We'll come back to this structure once we're about to start
        // doing more interesting things with Vulkan.
        vk::PhysicalDeviceFeatures deviceFeatures;

        // Create device
        vk::DeviceCreateInfo createInfo = vk::DeviceCreateInfo(
                vk::DeviceCreateFlags(),
                queueCreateInfos.size(),
                queueCreateInfos.data(),
                0, nullptr,
                PhysicalDevice::s_DeviceExtensions.size(),
                PhysicalDevice::s_DeviceExtensions.data(),
                &deviceFeatures
        );

        if (m_Debug) {
            createInfo.enabledLayerCount = Debug::s_ValidationLayers.size();
            createInfo.ppEnabledLayerNames = Debug::s_ValidationLayers.data();
        }

        m_Device = m_GPU->GetNative().createDevice(createInfo);

        Queues::s_GraphicsQueue = m_Device.getQueue(indices.graphicsFamily.value(), 0);
        Queues::s_PresentQueue = m_Device.getQueue(indices.presentFamily.value(), 0);
    }

    Device::~Device() {
        NR_CORE_INFO("DELETING LOGICAL DEVICE");
        vkDestroyDevice(m_Device, nullptr);
    }
}