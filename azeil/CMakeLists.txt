cmake_minimum_required(VERSION 2.8)

project(azeil)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(${PROJECT_NAME} "main.cpp")
set(SOURCES stamp_entry.cpp)
