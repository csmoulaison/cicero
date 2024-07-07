cmake_minimum_required(VERSION 3.28.0)

set(PROJECT_NAME cicero)
project(${PROJECT_NAME})

file(GLOB_RECURSE SRC "*.c" "*.h")

add_executable(${PROJECT_NAME} ${SRC})
