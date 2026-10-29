cmake_minimum_required(VERSION 3.25)
project(Chapter01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Standalone fallback if built directly rather than from root
if(NOT TARGET SDL3::SDL3)
    find_package(SDL3 3.0 QUIET)
    if(NOT SDL3_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.4.2
            GIT_SHALLOW TRUE
        )
        FetchContent_MakeAvailable(SDL3)
    endif()
endif()

add_executable(Chapter01
    src/main.cpp
        src/Game.cpp
        includes/Game.h
)

target_include_directories(Chapter01 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(Chapter01 PRIVATE
    SDL3::SDL3
)
