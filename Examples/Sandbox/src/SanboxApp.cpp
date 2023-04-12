#include <Neuron/Neuron.h>
#include <Neuron/Core/Entrypoint.h>

class SandboxLayer : public Neuron::Layer {
public:
    SandboxLayer() : Layer("SandboxLayer") {}

    ~SandboxLayer() override = default;

    void OnAttach() override {
        NR_INFO("Layer attached: {}", m_DebugName);
    }

    void OnDetach() override {
        NR_INFO("Layer detached: {}", m_DebugName);
    }

    void OnUpdate(Neuron::Timestep ts) override {
    }

    void OnImGuiRender() override {
    }

    void OnEvent(Neuron::Event &e) override {
    }
};

class Sandbox : public Neuron::Application {
public:
    explicit Sandbox(const Neuron::ApplicationSpecification &specification)
            : Neuron::Application(specification) {
        NR_INFO("Creating Sandbox App");
        PushLayer(new SandboxLayer());
    }

    ~Sandbox() override {
        NR_INFO("Destroying Sandbox");
    }
};


Neuron::Application *Neuron::CreateApplication(Neuron::ApplicationCommandLineArgs args) {
    ApplicationSpecification spec;
    spec.Name = "Sandbox";
    spec.WorkingDirectory = "./";
    spec.CommandLineArgs = args;

    return new Sandbox(spec);
}