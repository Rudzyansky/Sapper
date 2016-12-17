cmake_minimum_required(VERSION 3.6)
project(sapper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wmultichar -lncursesw")

set(SOURCE_FILES main.cpp Sapper.cpp Sapper.h)
add_executable(sapper ${SOURCE_FILES})