cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(Citadel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories
add_subdirectory(BulletFarm)

add_subdirectory(V8Engine)

add_subdirectory(UnitTest)

# Citadel project
file(GLOB_RECURSE CITADEL_SOURCES "Citadel/src/*.cpp" "Citadel/src/*.h")

add_executable(Citadel ${CITADEL_SOURCES})

target_include_directories(Citadel PRIVATE
    V8Engine/vendor/spdlog/include
    V8Engine/src
    V8Engine/vendor
    V8Engine/vendor/math/glm
    BulletFarm/src
)

target_link_libraries(Citadel PRIVATE
    V8Engine
    BulletFarm
)

# Configuration-specific settings
target_compile_definitions(Citadel PRIVATE
    V8_PLATFORM_MAC
    $<$<CONFIG:Debug>:CITADEL_DEBUG>
    $<$<CONFIG:Release>:CITADEL_RELEASE>
    $<$<CONFIG:Dist>:CITADEL_DIST>
)

set_target_properties(Citadel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
    RUNTIME_OUTPUT_DIRECTORY_DIST ${CMAKE_BINARY_DIR}/bin/Dist
)