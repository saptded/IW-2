cmake_minimum_required(VERSION 3.17)
project(IW_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")

set(SOURCES_FOR_STATIC libs/matrix_count/src/matrix_count.c)

add_library(matrix_count STATIC ${SOURCES_FOR_STATIC})
target_include_directories(matrix_count PUBLIC libs/matrix_count/include)

add_executable(IW_2 main.c)
target_link_libraries(IW_2 matrix_count)