cmake_minimum_required(VERSION 3.15)
project(Rule30 CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Rule30
    src/main.cpp
    src/simulation.cpp
    src/rendering.cpp
    src/configParsing.cpp
)
set_target_properties(Rule30 PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

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

target_link_libraries(Rule30
    PRIVATE 
        raylib
        tomlplusplus::tomlplusplus
)
