cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin )

set(PROJECT_NAME cicero_source_generator)
project(${PROJECT_NAME})

file(GLOB_RECURSE SRC "../src/*.c")

add_executable(${PROJECT_NAME} ${SRC})
