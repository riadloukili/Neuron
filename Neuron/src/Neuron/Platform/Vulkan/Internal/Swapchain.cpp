#include "nrpch.h"
#include "Swapchain.h"
#include "Queues.h"

namespace Neuron::Vulkan::Internal {
    Swapchain::Swapchain(const Ref <PhysicalDevice> &physicalDevice, const Ref <Device> &device,
                         const Ref <Surface> &surface, Window *window) : m_Device(device) {
        NR_CORE_INFO("CREATING SWAPCHAIN");
        CreateSwapchain(physicalDevice, surface, window);
        CreateImageViews();
    }

    Swapchain::~Swapchain() {
        NR_CORE_INFO("DELETING SWAPCHAIN");

        for (auto imageView: m_SwapchainImageViews) {
            m_Device->GetNative().destroyImageView(imageView);
        }
        m_Device->GetNative().destroySwapchainKHR(m_Swapchain);
    }

    void Swapchain::CreateSwapchain(const Ref <PhysicalDevice> &physicalDevice,
                                    const Ref <Surface> &surface, Window *window) {
        auto swapchainSupport = physicalDevice->QuerySwapchainSupport();

        vk::SurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapchainSupport.formats);
        vk::PresentModeKHR presentMode = ChooseSwapPresentMode(swapchainSupport.presentModes);
        vk::Extent2D extent = ChooseSwapExtent(swapchainSupport.capabilities, window->GetFramebufferSize());

        m_ImageCount = swapchainSupport.capabilities.minImageCount + 1;

        if (swapchainSupport.capabilities.maxImageCount > 0 &&
            m_ImageCount > swapchainSupport.capabilities.maxImageCount) {
            m_ImageCount = swapchainSupport.capabilities.maxImageCount;
        }

        NR_CORE_INFO("Swapchain has {} images", m_ImageCount);

        vk::SwapchainCreateInfoKHR createInfo = vk::SwapchainCreateInfoKHR(
                vk::SwapchainCreateFlagsKHR(),
                surface->GetNative(), m_ImageCount,
                surfaceFormat.format,
                surfaceFormat.colorSpace, extent, 1,
                vk::ImageUsageFlagBits::eColorAttachment);

        QueueFamilyIndices indices = Queues::FindQueueFamilies(physicalDevice, surface);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = vk::SharingMode::eExclusive;
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        // We can specify that a certain transform should be applied to images in the
        // swap chain if it is supported (supportedTransforms in capabilities), like
        // a 90-degree clockwise rotation or horizontal flip. To specify that you do
        // not want any transformation, simply specify the current transformation.
        createInfo.preTransform = swapchainSupport.capabilities.currentTransform;

        // The compositeAlpha field specifies if the alpha channel should be used for
        // blending with other windows in the window system. You'll almost always
        // want to simply ignore the alpha channel, hence VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR.
        createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;

        createInfo.presentMode = presentMode;
        // If the clipped member is set to VK_TRUE then that means that we don't care
        // about the color of pixels that are obscured, for example because another
        // window is in front of them. Unless you really need to be able to read
        // these pixels back and get predictable results, you'll get the best performance
        // by enabling clipping.
        createInfo.clipped = VK_TRUE;

        // With Vulkan, it's possible that your swap chain becomes invalid or
        // unoptimized while your application is running, for example because the
        // window was resized. In that case the swap chain actually needs to be
        // recreated from scratch and a reference to the old one must be specified
        // in this field.
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        m_Swapchain = m_Device->GetNative().createSwapchainKHR(createInfo);

        m_SwapchainImages = m_Device->GetNative().getSwapchainImagesKHR(m_Swapchain);

        m_SwapchainImageFormat = surfaceFormat.format;
        m_SwapchainExtent = extent;
    }

    void Swapchain::CreateImageViews() {
        m_SwapchainImageViews.resize(m_SwapchainImages.size());

        for (size_t i = 0; i < m_SwapchainImages.size(); i++) {
            vk::ImageViewCreateInfo createInfo = vk::ImageViewCreateInfo(
                    vk::ImageViewCreateFlags(),
                    m_SwapchainImages[i],
                    vk::ImageViewType::e2D,
                    m_SwapchainImageFormat,
                    vk::ComponentMapping(
                            vk::ComponentSwizzle::eIdentity,
                            vk::ComponentSwizzle::eIdentity,
                            vk::ComponentSwizzle::eIdentity,
                            vk::ComponentSwizzle::eIdentity
                    ),
                    vk::ImageSubresourceRange(
                            vk::ImageAspectFlags(vk::ImageAspectFlagBits::eColor),
                            0,
                            1,
                            // If you were working on a stereographic 3D application, then you would
                            // create a swap chain with multiple layers. You could then create
                            // multiple image views for each image representing the views for the
                            // left and right eyes by accessing different layers.
                            0,
                            1
                    )
            );
            m_SwapchainImageViews[i] = m_Device->GetNative().createImageView(createInfo);
        }
    }

    vk::SurfaceFormatKHR Swapchain::ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats) {
        for (const auto &availableFormat: availableFormats) {
            if (availableFormat.format == vk::Format::eB8G8R8A8Srgb &&
                availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }

    vk::PresentModeKHR Swapchain::ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes) {
        for (const auto &availablePresentMode: availablePresentModes) {
            if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
                return availablePresentMode;
            }
        }
        // Only the _vk::PresentModeKHR::eFifo_ mode is guaranteed to be available.
        return vk::PresentModeKHR::eFifo;
    }

    vk::Extent2D
    Swapchain::ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities, const glm::u32vec2 &framebufferSize) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        }

        vk::Extent2D actualExtent = {framebufferSize.x, framebufferSize.y};

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width,
                                        capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height,
                                         capabilities.maxImageExtent.height);

        return actualExtent;
    }

}
