project "GoogleTest"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    vendorpath = ""

    files
    {
        "%{vendorpath}/googletest/src/**.h",
        "%{vendorpath}/googletest/src/gtest-all.cc",
        "%{vendorpath}/googletest/include/**.h",
    }

    includedirs
    {
        "%{vendorpath}/googletest/include",
        "%{vendorpath}/googletest",
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        staticruntime "on"
    
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
