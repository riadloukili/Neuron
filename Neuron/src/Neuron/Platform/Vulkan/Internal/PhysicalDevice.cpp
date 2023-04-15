#include "nrpch.h"
#include "PhysicalDevice.h"
#include "Queues.h"

namespace Neuron::Vulkan::Internal {

    PhysicalDevice::PhysicalDevice(const Ref <Instance> &instance, const Ref <Surface> &surface, bool debug)
            : m_Surface(surface), m_Debug(debug) {
        NR_CORE_INFO("CREATING PHYSICAL DEVICE");
        m_GPU = PickPhysicalDevice(instance);
        NR_CORE_INFO("CHOSEN GPU: {}", m_GPU.getProperties().deviceName);
    }

    PhysicalDevice::~PhysicalDevice() {
        NR_CORE_INFO("DELETING PHYSICAL DEVICE");
    };

    vk::PhysicalDevice
    PhysicalDevice::PickPhysicalDevice(const Ref <Instance> &instance) const {
        std::vector<vk::PhysicalDevice> availableDevices = instance->GetNative().enumeratePhysicalDevices();

        NR_CORE_ASSERT(!availableDevices.empty(), "Failed to find GPUs with Vulkan support!")

        uint32_t maxScore = 0;
        vk::PhysicalDevice chosenGPU = nullptr;
        for (auto gpu: availableDevices) {
            uint32_t score = 0;
            if (IsSuitable(gpu, m_Surface, score) && score > maxScore) {
                maxScore = score;
                chosenGPU = gpu;
            }
        }
        NR_CORE_ASSERT(chosenGPU, "Failed to find a suitable GPU!")

        NR_CORE_INFO("GPU score: {}", maxScore);

        return chosenGPU;
    }

    bool
    PhysicalDevice::IsSuitable(const vk::PhysicalDevice &device, const Ref <Surface> &surface, uint32_t &score) {

        QueueFamilyIndices indices = Queues::FindQueueFamilies(device, surface);

        bool extensionsSupported = CheckDeviceExtensionSupport(device);

        bool swapchainAdequate;
        if (extensionsSupported) {
            SwapchainSupportDetails swapchainSupport = QuerySwapchainSupport(device, surface);
            swapchainAdequate = !swapchainSupport.formats.empty() && !swapchainSupport.presentModes.empty();
        }


        score = 0;
        auto properties = device.getProperties();
        if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
            score += 1000;
        score += properties.limits.maxImageDimension2D;


        return indices.isComplete() && extensionsSupported && swapchainAdequate;
    }

    bool PhysicalDevice::CheckDeviceExtensionSupport(const vk::PhysicalDevice &device) {
        std::vector<vk::ExtensionProperties> availableExtensions = device.enumerateDeviceExtensionProperties();

        std::set<std::string> requiredExtensions(s_DeviceExtensions.begin(), s_DeviceExtensions.end());

        for (const auto &extension: availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    SwapchainSupportDetails
    PhysicalDevice::QuerySwapchainSupport(const vk::PhysicalDevice &device, const Ref <Surface> &surface) {
        SwapchainSupportDetails details;

        details.capabilities = device.getSurfaceCapabilitiesKHR(surface->GetNative());
        details.formats = device.getSurfaceFormatsKHR(surface->GetNative());
        details.presentModes = device.getSurfacePresentModesKHR(surface->GetNative());

        return details;
    }

    SwapchainSupportDetails PhysicalDevice::QuerySwapchainSupport() const {
        NR_CORE_ASSERT(m_GPU, "GPU not yet selected, creating Swapchain before selecting physical device?")
        return QuerySwapchainSupport(m_GPU, m_Surface);
    }

}
