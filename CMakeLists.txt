# Startup Citadel
cmake_minimum_required(VERSION 3.30)

project(Citadel VERSION 0.1.0.0
    DESCRIPTION "CMake for Citadel"
    LANGUAGES CXX
)

# Language
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DIST "-O2")
set(CMAKE_EXE_LINKER_FLAGS_DIST "-02")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}")
set(OBJ_DIR "${CMAKE_BINARY_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}")

# Use the custom directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OBJ_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_VS_INTDIR ${OBJ_DIR})

message(STATUS "Build Citadel, version: ${Citadel_VERSION_MAJOR}.${Citadel_VERSION_MINOR}.${Citadel_VERSION_PATCH}.${Citadel_VERSION_TWEAK}")
message(STATUS "${OUTPUT_DIR}")
message(STATUS "${OBJ_DIR}")

# message(${CMAKE_BINARY_DIR})
# message(${CMAKE_SYSTEM_NAME})
# message(${CMAKE_BUILD_TYPE})
# message(${CMAKE_SYSTEM_PROCESSOR})

configure_file(CitadelConfig.h.in CitadelConfig.h)

# add Library
add_subdirectory(V8Engine)

# add Exe
add_subdirectory(Citadel)