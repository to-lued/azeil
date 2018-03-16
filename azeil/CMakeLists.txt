cmake_minimum_required(VERSION 2.8)

project(azeil)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES 
	main.cpp 
	stamp_entry.cpp
	)
add_executable(${PROJECT_NAME} ${SOURCES})
