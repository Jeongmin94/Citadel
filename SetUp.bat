@echo off
REM GLFW premake5
set glfw=GLFWpremake5.lua
set glfwDestination=V8Engine\vendor\GLFW\premake5.lua
if exist "%glfw%" (
    copy "%glfw%" "%glfwDestination%"
    echo move done: %glfwDestination%
) else (
    echo file is missing: %glfw%
)

call vendor\bin\premake\premake5.exe vs2022
PAUSE