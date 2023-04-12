#include "nrpch.h"
#include "Application.h"
#include "Neuron/Utils/PlatformUtils.h"
#include "Neuron/Renderer/Renderer.h"

namespace Neuron {
    Application *Application::s_Instance = nullptr;

    Application::Application(Neuron::ApplicationSpecification specification) : m_Specification(
            std::move(specification)) {
        NR_CORE_ASSERT(!s_Instance, "Application already exists!")
        s_Instance = this;

        m_Window = Window::Create(WindowProps(m_Specification.Name, 1280, 720));
        m_Window->SetEventCallback(NR_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();
    }

    Application::~Application() {

        Renderer::Shutdown();
    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::Run() {
        while (m_Running) {
            float time = Time::GetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            if (!m_Minimized) {
                {
                    for (Layer *layer: m_LayerStack)
                        layer->OnUpdate(timestep);
                }
#if TODO
                m_ImGuiLayer->Begin();
                {
                    for (Layer* layer : m_LayerStack)
                        layer->OnImGuiRender();
                }
                m_ImGuiLayer->End();
#endif
            }
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(NR_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(NR_BIND_EVENT_FN(Application::OnWindowResize));
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
        if (e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}