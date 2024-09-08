cmake_minimum_required(VERSION 3.10)

project(Citadel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(
    BulletFarm/src
    V8Engine/vendor/spdlog/include
    V8Engine/src
    V8Engine/vendor/GLFW/include
    V8Engine/vendor/Glad/include
    V8Engine/vendor/ImGui
    UnitTest/vendor/googletest/googletest/include
    UnitTest/vendor/googletest/googletest
)

# Add subdirectories
add_subdirectory(BulletFarm)
add_subdirectory(V8Engine)
add_subdirectory(UnitTest)
add_subdirectory(V8Engine/vendor/GLFW)
add_subdirectory(V8Engine/vendor/Glad)
add_subdirectory(V8Engine/vendor/ImGui)
add_subdirectory(UnitTest/vendor/googletest)

# Citadel project
file(GLOB_RECURSE CITADEL_SOURCES "Citadel/src/*.cpp" "Citadel/src/*.h")

add_executable(Citadel ${CITADEL_SOURCES})

target_include_directories(Citadel PRIVATE
    V8Engine/vendor/spdlog/include
    V8Engine/src
    BulletFarm/src
)

target_link_libraries(Citadel PRIVATE
    BulletFarm
    V8Engine
)

# Configuration-specific settings
target_compile_definitions(Citadel PRIVATE
    V8_PLATFORM_WINDOWS
    $<$<CONFIG:Debug>:CITADEL_DEBUG>
    $<$<CONFIG:Release>:CITADEL_RELEASE>
    $<$<CONFIG:Dist>:CITADEL_DIST>
)

set_target_properties(Citadel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
    RUNTIME_OUTPUT_DIRECTORY_DIST ${CMAKE_BINARY_DIR}/bin/Dist
)