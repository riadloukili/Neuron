#pragma once

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace Neuron::Vulkan::Internal {

    class Instance {
    public:
        explicit Instance(std::string applicationName, bool debug = false);

        ~Instance();

        vk::Instance GetHandle() { return m_Instance; }

    private:
        void SetupInstance();
        std::vector<const char *> GetRequiredExtensions() const;
        void SetupDebugMessenger();
    private:
        vk::Instance m_Instance{nullptr};
        vk::DebugUtilsMessengerEXT m_DebugMessenger{nullptr};
        vk::DispatchLoaderDynamic m_DLDI;

        std::string m_ApplicationName;
        bool m_Debug;
    };

}

