#pragma once

#include "Neuron/Core/Window.h"

namespace Neuron {
    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;

        virtual void SwapBuffers() = 0;

        static Scope <GraphicsContext> Create(Window *window);
    };
}
