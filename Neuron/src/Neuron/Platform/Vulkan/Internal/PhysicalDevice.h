#pragma once

#include "Instance.h"

namespace Neuron::Vulkan::Internal {

    class PhysicalDevice {
    public:
        explicit PhysicalDevice(Ref<Instance> &instance, bool debug = false);

        ~PhysicalDevice();

        vk::PhysicalDevice GetNative() { return m_GPU; }

    private:
        vk::PhysicalDevice PickPhysicalDevice();

        bool IsSuitable(vk::PhysicalDevice &device, uint32_t &score) const;

        static bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    private:
        Ref<Instance> m_Instance;
        vk::PhysicalDevice m_GPU{nullptr};

        bool m_Debug;

        inline static const std::vector<const char *> s_DeviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#ifdef NR_PLATFORM_MACOS
                "VK_KHR_portability_subset",
#endif
        };
    };

}
