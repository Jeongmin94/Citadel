project "V8Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	-- for pch use
	pchheader "v8pch.h"
	-- for pch create
	pchsource "src/v8pch.cpp"

	files
	{
		"src/**.h",
        "src/**.cpp",
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.V8}",
		"%{IncludeDir.BulletFarm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.json}",
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
