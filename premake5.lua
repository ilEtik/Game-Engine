workspace "Game-Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "Game-Engine/vendor/glfw/include"
IncludeDir["glad"] = "Game-Engine/vendor/glad/include"

include "Game-Engine/vendor/glfw"
include "Game-Engine/vendor/glad"

project "Game-Engine"
	location "Game-Engine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "Game-Engine/src/gepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}"
	}

	links
	{
		"GLFW",
		"glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "GE_DISTRIBUTION"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Game-Engine/vendor/spdlog/include",
		"Game-Engine/src"
	}

	links
	{
		"Game-Engine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GE_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPYDIR} ../bin/" .. outputdir .. "/Game-Engine/Game-Engine.dll %{cfg.targetdir}")
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "GE_DISTRIBUTION"
		runtime "Release"
		optimize "on"