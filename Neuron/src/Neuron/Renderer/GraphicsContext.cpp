#include "nrpch.h"
#include "GraphicsContext.h"
#include "RendererAPI.h"
#include "Renderer.h"

namespace Neuron {
    Scope <GraphicsContext> GraphicsContext::Create(void *window) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
                return nullptr;
#if TODO
            case RendererAPI::API::Vulkan:
                return CreateScope<VulkanContext>(static_cast<GLFWwindow *>(window));
#endif
        }

        NR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}