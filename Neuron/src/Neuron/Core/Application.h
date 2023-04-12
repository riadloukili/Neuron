#pragma once

#include <string>

#include "Base.h"
#include "Window.h"
#include "Neuron/Events/Event.h"
#include "Neuron/Events/ApplicationEvent.h"
#include "LayerStack.h"

int main(int argc, char **argv);

namespace Neuron {
    struct ApplicationCommandLineArgs {
        int Count = 0;
        char **Args = nullptr;

        const char *operator[](int index) const {
            NR_CORE_ASSERT(index < Count && index >= 0, "Out of bound access to ApplicationCommandLineArgs")
            return Args[index];
        }
    };

    struct ApplicationSpecification {
        std::string Name = "Neuron Application";
        std::string WorkingDirectory;
        ApplicationCommandLineArgs CommandLineArgs;
    };

    class Application {
    public:
        explicit Application(ApplicationSpecification specification);

        virtual ~Application();

        void OnEvent(Event &e);

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        static Application &Get() { return *s_Instance; }

        Window &GetWindow() { return *m_Window; }

        void Close();

        const ApplicationSpecification &GetSpecification() const { return m_Specification; }

    private:

        void Run();

        bool OnWindowClose(WindowCloseEvent &e);

        bool OnWindowResize(WindowResizeEvent &e);

    private:
        ApplicationSpecification m_Specification;
        Scope<Window> m_Window;
        bool m_Running = true;
        bool m_Minimized = false;

        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
    private:
        static Application *s_Instance;

        friend int::main(int argc, char **argv);
    };

    // To be defined in the client
    Application *CreateApplication(ApplicationCommandLineArgs args);
}
