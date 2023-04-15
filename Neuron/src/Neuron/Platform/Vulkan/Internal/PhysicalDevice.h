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
        explicit PhysicalDevice(const Ref <Instance> &instance, const Ref <Surface> &surface, bool debug = false);

        ~PhysicalDevice();

        const vk::PhysicalDevice &GetNative() { return m_GPU; }

        [[nodiscard]] SwapchainSupportDetails QuerySwapchainSupport() const;

    private:
        vk::PhysicalDevice PickPhysicalDevice(const Ref <Instance> &instance) const;

        static bool IsSuitable(const vk::PhysicalDevice &device, const Ref <Surface> &surface, uint32_t &score);

        static bool CheckDeviceExtensionSupport(const vk::PhysicalDevice &device);

        static SwapchainSupportDetails
        QuerySwapchainSupport(const vk::PhysicalDevice &device, const Ref <Surface> &surface);

    private:
        vk::PhysicalDevice m_GPU{nullptr};
        Ref <Surface> m_Surface;

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
