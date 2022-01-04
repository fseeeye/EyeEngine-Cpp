-- ref: https://github.com/premake/premake-core/wiki/Your-First-Script

workspace "Eye"
    architecture "x86_64"
    startproject "GameSandbox"

    configurations
    {
        "Debug",
        "Release", -- fast version of Debug mode
        "Dist" -- distribution mode
    }

-- tokens ref: https://github.com/premake/premake-core/wiki/Tokens
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- vendor include directories structure which relative to solution root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Eye/vendor/GLFW/include"
IncludeDir["Glad"] = "Eye/vendor/Glad/include"

-- include `premake5.lua` of vendors 
include "Eye/vendor/GLFW"
include "Eye/vendor/Glad"

project "Eye"
    location "Eye"
    kind "SharedLib" -- dynamic library (DLL)
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- target directory
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- intermediate directory

    pchheader "eyepch.h"
    pchsource "Eye/src/eyepch.cpp"

    files -- project files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs -- addtional include directories
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    -- ref: https://github.com/premake/premake-core/wiki/filter
    filter "system:windows" -- filter for Windows platform
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest" -- windows SDK version

        -- ref: https://github.com/premake/premake-core/wiki/defines
        defines -- preprocessor definitions
        {
            "EYE_PLATFORM_WINDOWS",
            "EYE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        -- ref: https://github.com/premake/premake-core/wiki/postbuildcommands
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/GameSandbox") -- copy Eye Engine dll to GameSandbox bin dir
        }

    filter "configurations:Debug" -- filter for Debug mode
        defines "EYE_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release" -- filter for Release mode
        defines "EYE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist" -- filter for Distribution mode
        defines "EYE_DIST"
        buildoptions "/MD"
        optimize "On"


project "GameSandbox"
    location "GameSandbox"
    kind "ConsoleApp" -- exe
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- target directory
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- intermediate directory

    files -- project files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs -- addtional include directories
    {
        "Eye/vendor/spdlog/include",
        "Eye/src"
    }

    links
    {
        "Eye" -- reference to project "Eye"
    }

    -- ref: https://github.com/premake/premake-core/wiki/filter
    filter "system:windows" -- filter for Windows platform
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest" -- windows SDK version (set spec version or use "latest")

        -- ref: https://github.com/premake/premake-core/wiki/defines
        defines -- preprocessor definitions
        {
            "EYE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug" -- filter for Debug mode
        defines "EYE_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release" -- filter for Release mode
        defines "EYE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist" -- filter for Distribution mode
        defines "EYE_DIST"
        buildoptions "/MD"
        optimize "On"