#include "Neuron/Renderer/GraphicsContext.h"
#include "Neuron/Platform/Vulkan/Internal/Instance.h"

namespace Neuron::Vulkan {

    class VulkanContext : public GraphicsContext {
    public:
        explicit VulkanContext(GLFWwindow *window);

        ~VulkanContext() override;

        void Init() override;

        void SwapBuffers() override;

    private:
        Internal::Instance *m_Instance = nullptr;
        GLFWwindow *m_Window;
    };

}
