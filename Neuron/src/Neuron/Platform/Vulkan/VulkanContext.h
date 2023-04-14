#include "Neuron/Renderer/GraphicsContext.h"
#include "Neuron/Platform/Vulkan/Internal/Instance.h"
#include "Neuron/Platform/Vulkan/Internal/PhysicalDevice.h"
#include "Neuron/Platform/Vulkan/Internal/Surface.h"

namespace Neuron::Vulkan {

    class VulkanContext : public GraphicsContext {
    public:
        explicit VulkanContext(GLFWwindow *window);

        ~VulkanContext() override;

        void Init() override;

        void SwapBuffers() override;

    private:
        Ref <Internal::Instance> m_Instance;
        Ref <Internal::Surface> m_Surface;
        Ref <Internal::PhysicalDevice> m_GPU;

        GLFWwindow *m_Window;
    };

}
