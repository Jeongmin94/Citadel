workspace "Citadel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"  

project "V8Engine"
	location "V8Engine" 
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"  
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS", 
			"V8_BUILD_DLL"
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Citadel")
	}

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		optimize "On"

project "Citadel"
	location "Citadel"
	kind "ConsoleApp"
	language "C++"

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
		"V8Engine/src"
	}

	links
	{
		"V8Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"V8_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CITADEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CITADEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CITADEL_DIST"
		optimize "On"