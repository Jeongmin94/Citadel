@echo off
REM GLFW premake5
setlocal enabledelayedexpansion

set glfw=GLFWpremake5.lua
set glfwDestination=V8Engine\vendor\GLFW\premake5.lua

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

call vendor\bin\premake\premake5.exe vs2022
PAUSE