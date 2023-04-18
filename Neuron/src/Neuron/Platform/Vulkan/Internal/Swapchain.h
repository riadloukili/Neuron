
#include <vulkan/vulkan.hpp>
#include "PhysicalDevice.h"
#include "Neuron/Core/Window.h"
#include "Device.h"

namespace Neuron::Vulkan::Internal {

    class Swapchain {
    public:
        Swapchain(const Ref <PhysicalDevice> &physicalDevice, const Ref <Device> &device,
                  const Ref <Surface> &surface, Window *window);

        ~Swapchain();

        const vk::SwapchainKHR &GetNative() const { return m_Swapchain; }

        const vk::Format &GetFormat() const { return m_SwapchainImageFormat; }

        const vk::Extent2D &GetExtent() const { return m_SwapchainExtent; }

        uint32_t ImageCount() const { return m_ImageCount; }

    private:
        void CreateSwapchain(const Ref <PhysicalDevice> &physicalDevice, const Ref <Surface> &surface, Window *window);

        void CreateImageViews();

        static vk::SurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats);

        static vk::PresentModeKHR ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes);

        static vk::Extent2D
        ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities, const glm::u32vec2 &framebufferSize);

    private:
        Ref <Device> m_Device;

        vk::SwapchainKHR m_Swapchain{nullptr};
        std::vector<vk::Image> m_SwapchainImages;
        vk::Format m_SwapchainImageFormat;
        vk::Extent2D m_SwapchainExtent;
        std::vector<vk::ImageView> m_SwapchainImageViews;
        uint32_t m_ImageCount{};
        std::vector<vk::Framebuffer> m_SwapchainFramebuffers;
    };

}