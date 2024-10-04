project "BulletFarm"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on" 

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
        IncludeDir["json"]
	}

	includedirs
	{
		"src",
		"vendor/json",
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
