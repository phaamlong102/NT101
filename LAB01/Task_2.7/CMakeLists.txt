cmake_minimum_required(VERSION 4.1)
project(Task2_7)

set(CMAKE_CXX_STANDARD 20)

add_executable(Task2_7 main.cpp)
set(INPUT_FILES "input.txt")

foreach(FILE ${INPUT_FILES})
    configure_file(${FILE} ${CMAKE_CURRENT_BINARY_DIR}/${FILE} COPYONLY)
endforeach()
