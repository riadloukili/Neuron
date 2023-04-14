#pragma once

#include <vector>

namespace Neuron::Vulkan::Internal {

    class Debug {
    public:
        inline static const std::vector<const char *> s_ValidationLayers = {"VK_LAYER_KHRONOS_validation"};

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData
        ) {
            std::string type;
            switch (messageType) {
                case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
                    type = "general";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
                    type = "performance";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
                    type = "validation";
                    break;
                default:
                    NR_CORE_FATAL("unknown message type received.");
            }

            switch (messageSeverity) {
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                    NR_CORE_TRACE("[{0}]: {1}", type, pCallbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                    NR_CORE_INFO("[{0}]: {1}", type, pCallbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                    NR_CORE_WARN("[{0}]: {1}", type, pCallbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                    NR_CORE_ERROR("[{0}]: {1}", type, pCallbackData->pMessage);
                    break;
                default:
                    NR_CORE_FATAL("unknown message severity received.");
            }

            return VK_FALSE;
        }

        static vk::DebugUtilsMessengerEXT CreateDebugMessenger(
                vk::Instance &instance,
                vk::DispatchLoaderDynamic &dldi
        ) {
            auto createInfo = *GetDebugMessengerCreateInfo();
            return instance.createDebugUtilsMessengerEXT(createInfo, nullptr, dldi);
        }

        static void DestroyDebugUtilsMessengerEXT(
                vk::Instance &instance,
                vk::DebugUtilsMessengerEXT &messenger,
                vk::DispatchLoaderDynamic &dldi
        ) {
            instance.destroyDebugUtilsMessengerEXT(messenger, nullptr, dldi);
        }

        static vk::DebugUtilsMessengerCreateInfoEXT *GetDebugMessengerCreateInfo() {
            return new vk::DebugUtilsMessengerCreateInfoEXT(
                    {
                            vk::DebugUtilsMessengerCreateFlagsEXT(),
                            vk::DebugUtilsMessageSeverityFlagsEXT(
                                    // vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                                    // vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
                                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError),
                            vk::DebugUtilsMessageTypeFlagsEXT(
                                    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                                    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                                    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance),
                            DebugCallback
                    }
            );
        }
    };

}
