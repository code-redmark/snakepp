cmake_minimum_required(VERSION 3.10)
project(snakepp)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file (GLOB GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/*.c)

add_subdirectory(deps/glm)

if (UNIX AND NOT APPLE)
    set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_executable(snakepp
    ${SRC}
    ${GLAD_SRC}
)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)

    target_link_libraries(snakepp PRIVATE
        X11::X11
        X11::Xrandr
    )
endif()

target_include_directories(snakepp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
)

target_link_libraries(snakepp PRIVATE
    glfw
    glm
)