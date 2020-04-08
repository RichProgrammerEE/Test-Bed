workspace "TestBed"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}

project "TestBed"
    location "testBed"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
    }

    links
    {
    }


    filter "system:linux"
        pic "on"

        linkoptions
        {
            "-fuse-ld=gold"
        }

    filter "configurations:Debug"
        defines "DSP_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "DSP_RELEASE"
        optimize "Speed"
        
        linkoptions
        {
            "-flto"
        }
