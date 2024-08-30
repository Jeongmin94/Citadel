@echo off
setlocal enabledelayedexpansion

REM GLFW premake5

set glfw=Scripts\GLFWpremake5.lua
set glfwDestination=V8Engine\vendor\GLFW\premake5.lua

echo Init premake5 for GLFW

if exist "%glfw%" (
    if not exist "%glfwDestination%" (
        copy "%glfw%" "%glfwDestination%"
        echo copy done: %glfwDestination%
    ) else (
        fc "%glfw%" "%glfwDestination%" > nul
        if errorlevel 1 (
            copy "%glfw%" "%glfwDestination%"
            echo file updated: %glfwDestination%
        ) else (
            echo premake5.lua for GLFW script is already up to date
        )
    )
) else (
    echo file is missing: %glfw%
)

REM ImGui premake5

set imgui=Scripts\ImGuipremake5.lua
set imguiDestination=V8Engine\vendor\ImGui\premake5.lua

echo Init premake5 for ImGui

if exist "%imgui%" (
    if not exist "%imguiDestination%" (
        copy "%imgui%" "%imguiDestination%"
        echo copy done: %imguiDestination%
    ) else (
        fc "%imgui%" "%imguiDestination%" > nul
        if errorlevel 1 (
            copy "%imgui%" "%imguiDestination%"
            echo file updated: %imguiDestination%
        ) else (
            echo premake5.lua for ImGui script is already up to date
        )
    )
) else (
    echo file is missing: %imgui%
)

call vendor\bin\premake\premake5.exe vs2022
PAUSE