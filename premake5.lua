workspace "Citadel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

newoption {
	trigger = "UseImGuiDocking",
	description = "Enable ImGui Docking",
}

project "BulletFarm"
	location "BulletFarm"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on" 

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS", 
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
IncludeDir["ImGuiDocking"] = "V8Engine/vendor/ImGui-Docking"
IncludeDir["glm"] = "V8Engine/vendor/math/glm"
IncludeDir["gtest"] = "UnitTest/vendor/googletest/googletest"

-- include premake5.lua files in directory
include "V8Engine/vendor/GLFW"
include "V8Engine/vendor/Glad"
include "UnitTest/vendor/googletest"

ImGuiDir = ""
ImGuiLink = ""
if _OPTIONS["UseImGuiDocking"] then
	include "V8Engine/vendor/ImGui-Docking"
	ImGuiDir = IncludeDir.ImGuiDocking
	ImGuiLink = "ImGuiDocking"
else
	include "V8Engine/vendor/ImGui"
	ImGuiDir = IncludeDir.ImGui
	ImGuiLink = "ImGui"
end

print("ImGui Information")
print("--include path: " .. ImGuiDir)
print("--project: " .. ImGuiLink)

project "V8Engine"
	location "V8Engine" 
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- for pch use
	pchheader "v8pch.h"
	-- for pch create
	pchsource "V8Engine/src/v8pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.BulletFarm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",

		ImGuiDir,
	}

	links
	{
		"BulletFarm",
		"GLFW",			-- project GLFW
		"Glad", 		-- project Glad
		"opengl32.lib",

		ImGuiLink,
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS", 
			"V8_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS",
		}

		if _OPTIONS["UseImGuiDocking"] then
			defines { "USING_IMGUI_DOCK" }
		end

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		runtime "Release"
		optimize "on"


project "UnitTest"
	location "UnitTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	pchheader "utpch.h"
	pchsource "UnitTest/src/utpch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",

		"V8Engine/vendor/spdlog/include",
		"V8Engine/src",
		"%{IncludeDir.BulletFarm}",
		
		-- GoogleTest
		"%{IncludeDir.gtest}/include",
		"%{IncludeDir.gtest}", 
	}

	links
	{
		"GoogleTest",
		"V8Engine",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS",
			"UNIT_TEST",
		}

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		runtime "Release"
		optimize "on"

project "Citadel"
	location "Citadel"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

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
		"V8Engine/vendor",
		"%{IncludeDir.BulletFarm}",
		"%{IncludeDir.glm}",
		ImGuiDir,
	}

	links
	{
		"BulletFarm",
		"V8Engine",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS",
		}

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		runtime "Release"
		optimize "on"