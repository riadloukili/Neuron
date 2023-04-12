project "Neuron"
    kind "StaticLib"
    staticruntime "On"

    location "%{wks.location}/Neuron"

    targetdir (bin_dir)
    objdir (obj_dir)

    pchheader "%{wks.location}/Neuron/src/nrpch.h"
    pchsource "%{wks.location}/Neuron/src/nrpch.cpp"

    files {
        "%{wks.location}/Neuron/src/**.h",
        "%{wks.location}/Neuron/src/**.cpp",
        "%{wks.location}/Neuron/src/**.embed",
    }

    defines { "TODO=false" }

    includedirs
    {
        "%{wks.location}/Neuron/src"
    }

    useSpdlog()

    useGLFW()

    useGLM()

    useImGui()

    useVulkan()
    
