include "dependencies.lua"

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


group "Dependencies"
	-- include premake5.lua files in directory
	include "V8Engine/vendor/GLFW"
	include "V8Engine/vendor/Glad"
	include "UnitTest/vendor/googletest"
	include (ImGuiIncludePremake)
group ""

group "Tools"
	include "BulletFarm"
group ""

group "Core"
	include "V8Engine"
group ""

group "Game"
	include "Citadel"
group ""

group "Test"
	include "UnitTest"
group ""
