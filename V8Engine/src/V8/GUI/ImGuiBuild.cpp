/*
 * ref: https://github.com/ocornut/imgui/issues/1299
 * for creating 'imgui_impl_*** lib' to use in other files
 */

#include "v8pch.h"

#include <glad/glad.h> // for imgui_opengl3.cpp

#include "backends/imgui_impl_glfw.cpp"
#include "backends/imgui_impl_opengl3.cpp"
