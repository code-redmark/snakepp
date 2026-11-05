cmake_minimum_required(VERSION 3.10)
project(snakepp)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file (GLOB GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/*.c)

add_subdirectory(deps/glm)

find_package(glfw3 REQUIRED)

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