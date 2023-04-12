project "Sandbox"
    kind "ConsoleApp"
    staticruntime "On"

    location "%{wks.location}/Examples/Sandbox"

    targetdir (bin_dir)
    objdir (obj_dir)

    files {
        "%{wks.location}/Examples/Sandbox/src/**.h",
        "%{wks.location}/Examples/Sandbox/src/**.cpp",
    }

    defines
    {
    }

    includedirs
    {
        "%{wks.location}/Examples/Sandbox/src"
    }

    useSpdlog()

    useGLFW()

    useGLM()

    useImGui()

    useVulkan()
    
    useNeuron()