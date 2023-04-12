include "External/premake-lib"

workspace "Neuron"
    architecture "arm64"
    startproject "Sandbox"

    language "C++"
    cppdialect "C++17"

    configurations { "Debug", "Release", "Dist" }

    filter "configurations:Debug"
        defines { "NR_DEBUG" }
        runtime "Debug"
        symbols "on"
    filter "configurations:Release"
        defines { "NR_RELEASE" }
        runtime "Release"
        optimize "on"
    filter "configurations:Dist"
        defines { "NR_DIST" }
        runtime "Release"
        optimize "on"

    filter "system:windows"
        systemversion "latest"
        defines { "NR_PLATFORM_WINDOWS" }
    filter "system:linux"
        defines { "NR_PLATFORM_LINUX" }
    filter "system:macosx"
        defines { "NR_PLATFORM_MACOS" }

    filter { }

    output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    bin_dir = ("%{wks.location}/bin/" .. output_dir)
    obj_dir = ("%{wks.location}/bin-int/" .. output_dir)

include "dependencies.lua"

group "Dependencies"
    include "External"
group ""

group "Core"
    include "Neuron"
group ""

group "Examples"
    include "examples/Sandbox"
group ""