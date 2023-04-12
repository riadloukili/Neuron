VULKAN_SDK = os.getenv("VULKAN_SDK")

if VULKAN_SDK == nil then
    print("VULKAN_SDK environment variable not set!")
    os.exit(1)
end 

-- ------
-- Include directories
-- ------
neuron_include_dir = {}
-- Logging
neuron_include_dir["spdlog"] = "%{wks.location}/External/spdlog/include"
-- Windowing
neuron_include_dir["GLFW"] = "%{wks.location}/External/GLFW/include"
-- Math
neuron_include_dir["GLM"] = "%{wks.location}/External/glm"
-- GUI
neuron_include_dir["ImGui"] = "%{wks.location}/External/imgui"
-- Vulkan
neuron_include_dir["Vulkan"] = VULKAN_SDK .. "/include"
-- Neuron
neuron_include_dir["Neuron"] = "%{wks.location}/Neuron/src"

-- ------
-- Library directories
-- ------
neuron_lib_dir = {}
-- Vulkan
neuron_lib_dir["Vulkan"] = VULKAN_SDK .. "/lib"

-- ------
-- Functions
-- ------

-- spdlog
function includeSpdlog()
    includedirs { neuron_include_dir["spdlog"] }
end
function linkSpdlog()
    -- Do nothing
end
function useSpdlog()
    includeSpdlog()
    linkSpdlog()
end

-- GLFW
function includeGLFW()
    includedirs { neuron_include_dir["GLFW"] }
    defines { "GLFW_INCLUDE_NONE", "_CRT_SECURE_NO_WARNINGS" }
end
function linkGLFW()
    filter "kind:not StaticLib"
        links { "GLFW" }
    
    filter {"kind:not StaticLib", "system:macosx"}
        -- links { "Cocoa.framework", "IOKit.framework", "CoreVideo.framework" } -- This doesn't work with CMake or Clion
        linkoptions { "-framework Cocoa", "-framework IOKit", "-framework CoreVideo" }
    filter {}
end
function useGLFW()
    includeGLFW()
    linkGLFW()
end

-- GLM
function includeGLM()
    includedirs { neuron_include_dir["GLM"] }
    defines { "GLM_FORCE_RADIANS", "GLM_FORCE_DEPTH_ZERO_TO_ONE" }
end
function linkGLM()
    -- Do nothing
end
function useGLM()
    includeGLM()
    linkGLM()
end

-- ImGui
function includeImGui()
    includedirs { neuron_include_dir["ImGui"] }
end
function linkImGui()
    filter "kind:not StaticLib"
        links { "ImGui" }
    filter {}
end
function useImGui()
    includeImGui()
    linkImGui()
end

-- Vulkan
function includeVulkan()
    includedirs { neuron_include_dir["Vulkan"] }
end
function linkVulkan()
    filter "kind:not StaticLib"
        libdirs { neuron_lib_dir["Vulkan"] }
    filter {"kind:not StaticLib", "system:windows"}
        links { "vulkan-1" }
    filter {"kind:not StaticLib", "system:macosx"}
        links { "vulkan" }
    filter {"kind:not StaticLib", "system:linux"}
        links { "vulkan" }
    filter {}
end
function useVulkan()
    includeVulkan()
    linkVulkan()
end

-- Neuron
function includeNeuron()
    includedirs { neuron_include_dir["Neuron"] }
end
function linkNeuron()
    filter "kind:not StaticLib"
        links { "Neuron" }
    filter {}
end
function useNeuron()
    includeNeuron()
    linkNeuron()
end
