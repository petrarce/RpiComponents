# stop if cmake version below 3.11
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# project name and supported languages
project(electro-cat-rpi CXX)

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

include_directories(AFTER ./common/)

#find_package(ZeroMQ REQUIRED)
#add_subdirectory(./common/)
add_subdirectory(./client/)
#add_subdirectory(./server/)
#add_subdirectory(./test_path_detection/)





