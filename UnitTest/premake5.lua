project "UnitTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	pchheader "utpch.h"
	pchsource "src/utpch.cpp"

	files
	{
		"src/**.h",
        "src/**.cpp",
	}

	includedirs
	{
		"src",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.V8}",
		"%{IncludeDir.BulletFarm}",
		"%{IncludeDir.json}",
		
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