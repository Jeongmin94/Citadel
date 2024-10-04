project "Citadel"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.V8}",
		"%{IncludeDir.V8Vendor}",
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