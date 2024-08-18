cmake_minimum_required(VERSION 3.10)

# 솔루션 이름
project(Citadel)

# 아키텍처 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 구성 설정
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)

# 결과물 폴더 경로 설정
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(OBJ_DIR "${CMAKE_BINARY_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

# V8Engine 프로젝트 설정
file(GLOB V8Engine_HEADERS "V8Engine/src/*.h")
file(GLOB V8Engine_SOURCES "V8Engine/src/*.cpp")

add_library(V8Engine SHARED
    ${V8Engine_HEADERS}
    ${V8Engine_SOURCES}
)

set_target_properties(V8Engine PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(V8Engine PRIVATE
    V8Engine/vendor/spdlog/include
)

target_compile_definitions(V8Engine PRIVATE
    V8_PLATFORM_WND
    V8_BUILD_DLL
)

target_compile_options(V8Engine PRIVATE
    $<$<CONFIG:Debug>:-DCITADEL_DEBUG>
    $<$<CONFIG:Release>:-DCITADEL_RELEASE>
    $<$<CONFIG:Dist>:-DCITADEL_DIST>
)

target_link_options(V8Engine PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Dist>:-O2>
)

# Citadel 프로젝트 설정
file(GLOB Citadel_HEADERS "Citadel/src/*.h")
file(GLOB Citadel_SOURCES "Citadel/src/*.cpp")

add_executable(Citadel
    ${Citadel_HEADERS}
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

# Dist 구성에 대한 링크 플래그 설정
set(CMAKE_EXE_LINKER_FLAGS_DIST "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_SHARED_LINKER_FLAGS_DIST "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
