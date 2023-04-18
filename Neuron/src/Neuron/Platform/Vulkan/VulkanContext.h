#include "Neuron/Renderer/GraphicsContext.h"
#include "Neuron/Platform/Vulkan/Internal/Instance.h"
#include "Neuron/Platform/Vulkan/Internal/PhysicalDevice.h"
#include "Neuron/Platform/Vulkan/Internal/Surface.h"
#include "Neuron/Platform/Vulkan/Internal/Device.h"
#include "Neuron/Platform/Vulkan/Internal/Swapchain.h"
#include "Neuron/Platform/Desktop/DesktopWindow.h"

namespace Neuron::Vulkan {

    class VulkanContext : public GraphicsContext {
    public:
        explicit VulkanContext(Window *window);

        ~VulkanContext() override;

        void Init() override;

        void SwapBuffers() override;

    private:
        Ref <Internal::Instance> m_Instance;
        Ref <Internal::Surface> m_Surface;
        Ref <Internal::PhysicalDevice> m_GPU;
        Ref <Internal::Device> m_Device;
        Ref <Internal::Swapchain> m_Swapchain;

        Window *m_Window;
    };

}
