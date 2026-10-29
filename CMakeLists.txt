cmake_minimum_required(VERSION 3.25)
project(GameProgrammingCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Shared Dependencies
find_package(SDL3 3.0 QUIET)
if(NOT SDL3_FOUND)
    message(STATUS "[Root] SDL3 not found locally; fetching via FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.2
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(SDL3)
endif()

# Chapter subdirectories
add_subdirectory(Chapter01)
