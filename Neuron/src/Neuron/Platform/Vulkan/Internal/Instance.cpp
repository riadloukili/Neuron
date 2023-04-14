#include "nrpch.h"
#include "Instance.h"

#include <utility>
#include "Debug.h"


namespace Neuron::Vulkan::Internal {
    Instance::Instance(std::string applicationName, bool debug)
            : m_ApplicationName(std::move(applicationName)),
              m_Debug(debug) {
        NR_CORE_INFO("CREATING VULKAN INSTANCE");
        SetupInstance();
        m_DLDI = vk::DispatchLoaderDynamic(m_Instance, vkGetInstanceProcAddr);
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
        if (m_Debug && !CheckValidationLayerSupport()) {
            NR_CORE_ASSERT(false, "One or more validation layer is not supported!")
        }
        // App info
        vk::ApplicationInfo appInfo = vk::ApplicationInfo(
                m_ApplicationName.c_str(),
                VK_MAKE_VERSION(0, 0, 1),
                "Neuron",
                VK_MAKE_VERSION(0, 0, 1),
                VK_API_VERSION_1_0
        );

        auto extensions = GetRequiredExtensions();

        // Create info
        vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
                vk::InstanceCreateFlags(
#ifdef NR_PLATFORM_MACOS
                        vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR
#endif
                ),
                &appInfo,
                0,
                nullptr,
                extensions.size(),
                extensions.data()
        );

        if (m_Debug) {
            createInfo.enabledLayerCount = Debug::s_ValidationLayers.size();
            createInfo.ppEnabledLayerNames = Debug::s_ValidationLayers.data();
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

    bool Instance::CheckValidationLayerSupport() {
        auto availableLayers = vk::enumerateInstanceLayerProperties();

        std::set<std::string> requiredLayers(Debug::s_ValidationLayers.begin(), Debug::s_ValidationLayers.end());

        for (const auto &layer: availableLayers) {
            requiredLayers.erase(layer.layerName);
        }

        return requiredLayers.empty();
    }

    void Instance::SetupDebugMessenger() {
        if (!m_Debug) return;
        m_DebugMessenger = Debug::CreateDebugMessenger(m_Instance, m_DLDI);
    }

}