#include "nrpch.h"
#include "PhysicalDevice.h"

namespace Neuron::Vulkan::Internal {

    PhysicalDevice::PhysicalDevice(Ref <Instance> &instance, bool debug)
            : m_Instance(instance), m_Debug(debug) {
        NR_CORE_INFO("CREATING PHYSICAL DEVICE");
        m_GPU = PickPhysicalDevice();
        NR_CORE_INFO("CHOSEN GPU: {}", m_GPU.getProperties().deviceName);
    }

    PhysicalDevice::~PhysicalDevice() {
        NR_CORE_INFO("DELETING PHYSICAL DEVICE");
    };

    vk::PhysicalDevice PhysicalDevice::PickPhysicalDevice() {
        std::vector<vk::PhysicalDevice> availableDevices = m_Instance->GetNative().enumeratePhysicalDevices();

        NR_CORE_ASSERT(!availableDevices.empty(), "Failed to find GPUs with Vulkan support!")

        uint32_t maxScore = 0;
        vk::PhysicalDevice chosenGPU = nullptr;
        for (auto gpu: availableDevices) {
            uint32_t score = 0;
            if (IsSuitable(gpu, score) && score > maxScore) {
                maxScore = score;
                chosenGPU = gpu;
            }
        }
        NR_CORE_ASSERT(chosenGPU, "Failed to find a suitable GPU!")

        NR_CORE_INFO("GPU score: {}", maxScore);

        return chosenGPU;
    }

    bool PhysicalDevice::IsSuitable(vk::PhysicalDevice &device, uint32_t &score) const {
        score = 0;

        bool extensionsSupported = CheckDeviceExtensionSupport(device);
        score += extensionsSupported;

        auto properties = device.getProperties();
        if(properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
            score += 1000;

        score += properties.limits.maxImageDimension2D;

        return extensionsSupported;
    }

    bool PhysicalDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(s_DeviceExtensions.begin(), s_DeviceExtensions.end());

        for (const auto &extension: availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }


}
