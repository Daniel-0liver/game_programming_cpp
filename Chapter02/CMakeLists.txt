cmake_minimum_required(VERSION 3.25)
project(Chapter02 LANGUAGES CXX)

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

if(NOT TARGET SDL3_image::SDL3_image)
    find_package(SDL3_image 3.0 QUIET)
    if(NOT SDL3_image_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            SDL3_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-3.4.2
            GIT_SHALLOW TRUE
        )
        FetchContent_MakeAvailable(SDL3_image)
    endif()
endif()

add_executable(Chapter02
    src/main.cpp
    src/Game.cpp
    includes/Game.h
)

target_include_directories(Chapter02 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(Chapter02 PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)

# Copy assets folder to the build output directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
