cmake_minimum_required(VERSION 3.15)
project(Rule30 CXX)

# ------------------------------------------------------------------------------
# C++ Standard Configuration
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# External Dependencies
# ------------------------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

FetchContent_Declare(
    raygui
    URL https://github.com/raysan5/raygui/archive/refs/tags/4.0.tar.gz
)
FetchContent_MakeAvailable(raygui)

if (NOT TARGET raygui)
    add_library(raygui INTERFACE)
    target_include_directories(raygui INTERFACE ${raygui_SOURCE_DIR}/src)
endif()

# ------------------------------------------------------------------------------
# Executable Target
# ------------------------------------------------------------------------------
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
add_executable(Rule30
    ${ALL_SOURCES}
)


target_include_directories(Rule30
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Rule30
    PRIVATE 
        raylib
        raygui
        tomlplusplus::tomlplusplus
)