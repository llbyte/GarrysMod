cmake_minimum_required(VERSION 4.2)

project(GarrysMod
        VERSION 1.0.0
        LANGUAGES CXX
)

set(TARGET_NAME GarrysMod)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/MinHook.Dependencies.cmake)
include(cmake/ImGui.Dependencies.cmake)
include(cmake/GarrysMod.Target.cmake)