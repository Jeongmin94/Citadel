project(GoogleTest)

file(GLOB_RECURSE GTEST_SOURCES "googletest/src/*.cc" "googletest/include/gtest/*.h")

add_library(GoogleTest STATIC ${GTEST_SOURCES})

target_include_directories(GoogleTest PRIVATE
    googletest/include
    googletest
)

target_compile_definitions(GoogleTest PRIVATE
    V8_PLATFORM_WINDOWS
)

set_target_properties(GoogleTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
    RUNTIME_OUTPUT_DIRECTORY_DIST ${CMAKE_BINARY_DIR}/bin/Dist
)