#include "nrpch.h"
#include "RendererAPI.h"

namespace Neuron {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;

    Scope <RendererAPI> RendererAPI::Create() {
        switch (s_API) {
            case RendererAPI::API::None: NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
                return nullptr;
#if TODO
            case RendererAPI::API::Vulkan:
                return CreateScope<VulkanRendererAPI>();
#endif
        }

        NR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}