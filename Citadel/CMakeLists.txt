# Startup Citadel Client
cmake_minimum_required(VERSION 3.30)

file(GLOB_RECURSE Citadel_SOURCES "src/*.cpp" "src/*.h")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Build Citadel Client")

add_executable(Citadel
    ${Citadel_SOURCES}
)

target_include_directories(Citadel PRIVATE
    V8Engine/vendor/spdlog/include
    V8Engine/src
)

target_link_libraries(Citadel PRIVATE V8Engine)

target_compile_definitions(Citadel PRIVATE
    V8_PLATFORM_WND
)

target_compile_options(Citadel PRIVATE
    $<$<CONFIG:Debug>:-DCITADEL_DEBUG>
    $<$<CONFIG:Release>:-DCITADEL_RELEASE>
    $<$<CONFIG:Dist>:-DCITADEL_DIST>
)

target_link_options(Citadel PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Dist>:-O2>
)