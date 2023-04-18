#pragma once

#include "Neuron/Core/Window.h"
#include "Neuron/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Neuron {

    class DesktopWindow : public Window {
    public:
        explicit DesktopWindow(const WindowProps &props);

        virtual ~DesktopWindow();

        void OnUpdate() override;

        [[nodiscard]] uint32_t GetWidth() const override { return m_Data.Width; }

        [[nodiscard]] uint32_t GetHeight() const override { return m_Data.Height; }

        [[nodiscard]] const glm::u32vec2 GetFramebufferSize() const override;

        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

        [[nodiscard]] void *GetNativeWindow() const override { return m_Window; };

    private:
        void Init(const WindowProps &props);

        void Shutdown();

    private:
        GLFWwindow *m_Window = nullptr;
        Scope<GraphicsContext> m_Context;

        struct WindowData {
            std::string Title;
            uint32_t Width, Height;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

}
