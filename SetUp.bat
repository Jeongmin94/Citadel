@echo off
REM GLFW premake5
set glfw=GLFWpremake5.lua
set glfwDestination=V8Engine\vendor\GLFW\premake5.lua
if exist "%glfw%" (
    if not exist "%glfwDestination%" (
        copy "%glfw%" "%glfwDestination%"
        echo copy done: %glfwDestination%
    ) else (
        echo premake5.lua for GLFW script is already exist
    )
) else (
    echo file is missing: %glfw%
)

call vendor\bin\premake\premake5.exe vs2022
PAUSE