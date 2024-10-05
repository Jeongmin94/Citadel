-- Include directories relative to root folder(solution directory)
IncludeDir = {}
IncludeDir["BulletFarm"] 			= "%{wks.location}/BulletFarm/src"
IncludeDir["json"]					= "%{wks.location}/BulletFarm/vendor/json"

IncludeDir["GLFW"] 					= "%{wks.location}/V8Engine/vendor/GLFW/include"
IncludeDir["Glad"] 					= "%{wks.location}/V8Engine/vendor/Glad/include"
IncludeDir["ImGui"] 				= "%{wks.location}/V8Engine/vendor/ImGui"
IncludeDir["ImGuiDocking"] 			= "%{wks.location}/V8Engine/vendor/ImGui-Docking"
IncludeDir["glm"] 					= "%{wks.location}/V8Engine/vendor/math/glm"
IncludeDir["spdlog"]				= "%{wks.location}/V8Engine/vendor/spdlog/include"
IncludeDir["V8"]					= "%{wks.location}/V8Engine/src"
IncludeDir["V8Vendor"]				= "%{wks.location}/V8Engine/vendor"

IncludeDir["gtest"] 				= "%{wks.location}/UnitTest/vendor/googletest/googletest"

ImGuiDir = ""
ImGuiLink = ""
ImGuiIncludePremake = ""
if _OPTIONS["UseImGuiDocking"] then
	ImGuiIncludePremake = "V8Engine/vendor/ImGui-Docking"
	ImGuiDir = IncludeDir.ImGuiDocking
	ImGuiLink = "ImGuiDocking"
else
	ImGuiIncludePremake = "V8Engine/vendor/ImGui"
	ImGuiDir = IncludeDir.ImGui
	ImGuiLink = "ImGui"
end

print("ImGui Information")
print("--include path: " .. ImGuiDir)
print("--project: " .. ImGuiLink)
