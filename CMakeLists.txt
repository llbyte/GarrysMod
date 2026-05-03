cmake_minimum_required(VERSION 4.2)
project(GarrysMod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        minhook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook
        GIT_TAG v1.3.4
)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.92.7
)

FetchContent_MakeAvailable(minhook imgui)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

add_library(GarrysMod SHARED
        ${SOURCES}
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp)

target_include_directories(GarrysMod PRIVATE
        src
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends)

target_link_libraries(GarrysMod PRIVATE minhook d3d9)