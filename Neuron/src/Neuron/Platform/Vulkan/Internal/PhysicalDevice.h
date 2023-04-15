#pragma once

#include "Instance.h"
#include "Surface.h"

namespace Neuron::Vulkan::Internal {

    struct SwapchainSupportDetails {
        vk::SurfaceCapabilitiesKHR capabilities{};
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    class PhysicalDevice {
    public:
        explicit PhysicalDevice(Ref <Instance> &instance, Ref <Surface> &surface, bool debug = false);

        ~PhysicalDevice();

        vk::PhysicalDevice GetNative() { return m_GPU; }

    private:
        vk::PhysicalDevice PickPhysicalDevice();

        bool IsSuitable(vk::PhysicalDevice &device, uint32_t &score) const;

        static bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

        [[nodiscard]] SwapchainSupportDetails QuerySwapchainSupport(vk::PhysicalDevice device) const;

    private:
        Ref <Instance> &m_Instance;
        Ref <Surface> &m_Surface;
        vk::PhysicalDevice m_GPU{nullptr};

        bool m_Debug;

        friend class Device;
        inline static const std::vector<const char *> s_DeviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#ifdef NR_PLATFORM_MACOS
                "VK_KHR_portability_subset",
#endif
        };
    };

}
