cmake_minimum_required(VERSION 3.20)

project(tcomp "CXX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/structs.cpp
    ${CMAKE_SOURCE_DIR}/utils.cpp
)