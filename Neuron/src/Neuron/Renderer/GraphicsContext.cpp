#include "nrpch.h"
#include "GraphicsContext.h"
#include "RendererAPI.h"
#include "Renderer.h"
#include "Neuron/Platform/Vulkan/VulkanContext.h"
#include "Neuron/Platform/Desktop/DesktopWindow.h"

namespace Neuron {
    Scope <GraphicsContext> GraphicsContext::Create(Window *window) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
                return nullptr;
            case RendererAPI::API::Vulkan:
                return CreateScope<Vulkan::VulkanContext>(window);
        }

        NR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}