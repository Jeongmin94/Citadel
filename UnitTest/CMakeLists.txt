project(UnitTest)

add_subdirectory(vendor/googletest)

file(GLOB_RECURSE UNITTEST_SOURCES "src/*.cpp" "src/*.h")

add_executable(UnitTest ${UNITTEST_SOURCES} src/UnitTest.cpp)

target_include_directories(UnitTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../V8Engine/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../V8Engine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../BulletFarm/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest
)

target_link_libraries(UnitTest PRIVATE
    GoogleTest
    V8Engine
    BulletFarm
)

target_precompile_headers(UnitTest PRIVATE src/utpch.h)

target_compile_definitions(UnitTest PRIVATE
    V8_PLATFORM_MAC
    UNIT_TEST
    $<$<CONFIG:Debug>:CITADEL_DEBUG>
    $<$<CONFIG:Release>:CITADEL_RELEASE>
    $<$<CONFIG:Dist>:CITADEL_DIST>
)

set_target_properties(UnitTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
    RUNTIME_OUTPUT_DIRECTORY_DIST ${CMAKE_BINARY_DIR}/bin/Dist
)