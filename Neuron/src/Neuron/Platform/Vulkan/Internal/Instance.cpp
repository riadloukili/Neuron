#include "nrpch.h"
#include "Instance.h"
#include "Debug.h"


namespace Neuron::Vulkan::Internal {
    Instance::Instance(std::string applicationName, bool debug)
            : m_ApplicationName(std::move(applicationName)),
              m_Debug(debug) {
        NR_CORE_INFO("CREATING VULKAN INSTANCE");
        SetupInstance();
        SetupDebugMessenger();
    }

    Instance::~Instance() {
        NR_CORE_INFO("DELETING VULKAN INSTANCE");
        if (m_Debug) {
            Debug::DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, m_DLDI);
        }
        m_Instance.destroy();
    }

    void Instance::SetupInstance() {
        // App info
        vk::ApplicationInfo appInfo = vk::ApplicationInfo(
                m_ApplicationName.c_str(),
                VK_MAKE_VERSION(0, 0, 1),
                "Neuron",
                VK_MAKE_VERSION(0, 0, 1),
                VK_API_VERSION_1_0
        );

        auto extensions = GetRequiredExtensions();

        std::vector<const char *> layers;
        if (m_Debug) {
            layers = Debug::s_ValidationLayers;
        }

        // Create info
        vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
                vk::InstanceCreateFlags(
#ifdef NR_PLATFORM_MACOS
                        vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR
#endif
                ),
                &appInfo,
                layers.size(),
                layers.data(),
                extensions.size(),
                extensions.data()
        );

        if (m_Debug) {
            createInfo.pNext = Debug::GetDebugMessengerCreateInfo();
        }

        m_Instance = vk::createInstance(createInfo);
    }

    std::vector<const char *> Instance::GetRequiredExtensions() const {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef NR_PLATFORM_MACOS
        extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif

        if (m_Debug) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }

    void Instance::SetupDebugMessenger() {
        if (!m_Debug) return;
        m_DLDI = vk::DispatchLoaderDynamic(m_Instance, vkGetInstanceProcAddr);
        m_DebugMessenger = Debug::CreateDebugMessenger(m_Instance, m_DLDI);
    }

}