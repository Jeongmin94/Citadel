project(ImGuiDocking)

file(GLOB IMGUI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_library(ImGuiDocking STATIC ${IMGUI_SOURCES})

target_include_directories(ImGuiDocking PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(ImGuiDocking PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
        RUNTIME_OUTPUT_DIRECTORY_DIST ${CMAKE_BINARY_DIR}/bin/Dist
)