#pragma once

#if TODO
#include "VertexArray.h"
#endif

#include <glm/glm.hpp>
#include "Neuron/Core/Base.h"

namespace Neuron {

    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0, Vulkan = 1
        };
    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

#if TODO
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
        virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

        virtual void SetLineWidth(float width) = 0;
#endif

        static API GetAPI() { return s_API; }
        static Scope<RendererAPI> Create();
    private:
        static API s_API;
    };

}