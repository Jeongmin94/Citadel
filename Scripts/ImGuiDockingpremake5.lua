project "ImGuiDocking"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"imconfig.h",
		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imgui.cpp",
		"imgui.h",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"