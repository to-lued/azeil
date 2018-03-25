cmake_minimum_required(VERSION 2.8)

project(azeil)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(SOURCES 
	main.cpp
	stamp_entry.cpp
	stamp_logfile.cpp
	)
add_executable(${PROJECT_NAME} ${SOURCES})
