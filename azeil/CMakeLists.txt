cmake_minimum_required(VERSION 2.8)

project(azeil)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(SOURCES 
	main.cpp
	sqlite/sqlite3.c
	sqlite/sqlite3.h
	stampdb.cpp
	stampdb.h
	)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sqlite PRIVATE dbwrapper)
target_link_libraries(${PROJECT_NAME}
	pthread
	dl
	)
