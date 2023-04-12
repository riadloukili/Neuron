project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    location "%{wks.location}/External/GLFW"

    targetdir (bin_dir)
    objdir (obj_dir)

    files
    {
        "%{wks.location}/External/GLFW/include/GLFW/glfw3.h",
        "%{wks.location}/External/GLFW/include/GLFW/glfw3native.h",
        "%{wks.location}/External/GLFW/src/context.c",
        "%{wks.location}/External/GLFW/src/init.c",
        "%{wks.location}/External/GLFW/src/input.c",
        "%{wks.location}/External/GLFW/src/monitor.c",
        
        "%{wks.location}/External/GLFW/src/platform.c",
        "%{wks.location}/External/GLFW/src/vulkan.c",
        "%{wks.location}/External/GLFW/src/window.c",
        "%{wks.location}/External/GLFW/src/egl_context.c",
        "%{wks.location}/External/GLFW/src/osmesa_context.c",

        "%{wks.location}/External/GLFW/src/null_init.c",
        "%{wks.location}/External/GLFW/src/null_monitor.c",
        "%{wks.location}/External/GLFW/src/null_window.c",
        "%{wks.location}/External/GLFW/src/null_joystick.c",
    }

    filter "system:macosx"
        pic "On"
        files
        {
            "%{wks.location}/External/GLFW/src/cocoa_time.c",
            "%{wks.location}/External/GLFW/src/posix_module.c",
            "%{wks.location}/External/GLFW/src/posix_thread.c",
            "%{wks.location}/External/GLFW/src/cocoa_init.m",
            "%{wks.location}/External/GLFW/src/cocoa_joystick.m",
            "%{wks.location}/External/GLFW/src/cocoa_monitor.m",
            "%{wks.location}/External/GLFW/src/cocoa_window.m",
            "%{wks.location}/External/GLFW/src/nsgl_context.m",
        }

        defines
        {
            "_GLFW_COCOA"
        }
        

    filter "system:linux"
        pic "On"
        systemversion "latest"
        files
        {
            "%{wks.location}/External/GLFW/src/x11_init.c",
            "%{wks.location}/External/GLFW/src/x11_monitor.c",
            "%{wks.location}/External/GLFW/src/x11_window.c",
            "%{wks.location}/External/GLFW/src/xkb_unicode.c",
            "%{wks.location}/External/GLFW/src/posix_time.c",
            "%{wks.location}/External/GLFW/src/posix_thread.c",
            "%{wks.location}/External/GLFW/src/glx_context.c",
            "%{wks.location}/External/GLFW/src/egl_context.c",
            "%{wks.location}/External/GLFW/src/osmesa_context.c",
            "%{wks.location}/External/GLFW/src/linux_joystick.c"
        }

        defines
        {
            "_GLFW_X11"
        }

    filter "system:windows"
        systemversion "latest"

        files
        {
            "%{wks.location}/External/GLFW/src/win32_init.c",
            "%{wks.location}/External/GLFW/src/win32_joystick.c",
            "%{wks.location}/External/GLFW/src/win32_monitor.c",
            "%{wks.location}/External/GLFW/src/win32_time.c",
            "%{wks.location}/External/GLFW/src/win32_thread.c",
            "%{wks.location}/External/GLFW/src/win32_window.c",
            "%{wks.location}/External/GLFW/src/wgl_context.c",
            "%{wks.location}/External/GLFW/src/egl_context.c",
            "%{wks.location}/External/GLFW/src/osmesa_context.c"
        }

        defines 
        { 
            "_GLFW_WIN32",
        }

    filter {}

project "ImGui"
    kind "StaticLib"
    staticruntime "On"

    location "%{wks.location}/External/imgui"

    targetdir (bin_dir)
    objdir (obj_dir)

    files
    {
        "%{wks.location}/External/imgui/imconfig.h",
        "%{wks.location}/External/imgui/imgui.h",
        "%{wks.location}/External/imgui/imgui.cpp",
        "%{wks.location}/External/imgui/imgui_draw.cpp",
        "%{wks.location}/External/imgui/imgui_internal.h",
        "%{wks.location}/External/imgui/imgui_tables.cpp",
        "%{wks.location}/External/imgui/imgui_widgets.cpp",
        "%{wks.location}/External/imgui/imstb_rectpack.h",
        "%{wks.location}/External/imgui/imstb_textedit.h",
        "%{wks.location}/External/imgui/imstb_truetype.h",
        "%{wks.location}/External/imgui/imgui_demo.cpp",

        "%{wks.location}/External/imgui/backends/imgui_impl_glfw.h",
        "%{wks.location}/External/imgui/backends/imgui_impl_glfw.cpp",
        "%{wks.location}/External/imgui/backends/imgui_impl_vulkan.h",
        "%{wks.location}/External/imgui/backends/imgui_impl_vulkan.cpp",
    }

    
    includeImGui()

    includeGLFW()
    
    includeVulkan()
