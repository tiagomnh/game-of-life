cmake_minimum_required(VERSION 3.10)
project(game-of-life)

set(${CMAKE_BINARY_DIR} build)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ConfigFile.cpp
    src/GameOfLife.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)