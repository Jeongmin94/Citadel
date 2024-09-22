project(BulletFarm)

file(GLOB_RECURSE BULLETFARM_SOURCES "src/*.cpp" "src/*.h")

add_library(BulletFarm STATIC ${BULLETFARM_SOURCES})

target_include_directories(BulletFarm PRIVATE
    src
)

target_compile_definitions(BulletFarm PRIVATE
    V8_PLATFORM_MAC
    $<$<CONFIG:Debug>:CITADEL_DEBUG>
    $<$<CONFIG:Release>:CITADEL_RELEASE>
    $<$<CONFIG:Dist>:CITADEL_DIST>
)

set_target_properties(BulletFarm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
    RUNTIME_OUTPUT_DIRECTORY_DIST ${CMAKE_BINARY_DIR}/bin/Dist
)