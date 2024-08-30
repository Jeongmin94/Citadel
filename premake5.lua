workspace "Citadel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

project "BulletFarm"
	location "BulletFarm"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS", 
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Citadel")
	}

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		runtime "Release"
		optimize "On"

-- Include directories relative to root folder(solution directory)
IncludeDir = {}
IncludeDir["BulletFarm"] = "BulletFarm/src"
IncludeDir["GLFW"] = "V8Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "V8Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "V8Engine/vendor/ImGui"

-- include premake5.lua files in directory
include "V8Engine/vendor/GLFW"
include "V8Engine/vendor/Glad"
include "V8Engine/vendor/ImGui"

project "V8Engine"
	location "V8Engine" 
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- for pch use
	pchheader "v8pch.h"
	-- for pch create
	pchsource "V8Engine/src/v8pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp" 
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.BulletFarm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
	}

	links
	{
		"BulletFarm",
		"GLFW",			-- project GLFW
		"Glad", 		-- project Glad
		"ImGui",		-- project ImGui
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS", 
			"V8_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Citadel")
	}

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		runtime "Release"
		optimize "On"

project "Citadel"
	location "Citadel"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"V8Engine/vendor/spdlog/include",
		"V8Engine/src",
		"%{IncludeDir.BulletFarm}",
	}

	links
	{
		"V8Engine",
		"BulletFarm",
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		runtime "Release"
		optimize "On"