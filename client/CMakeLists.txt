cmake_minimum_required(VERSION 3.11)
project(client)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmakemodules/)

find_package(Qt5 COMPONENTS Core Qml Quick Gui REQUIRED)
if (NOT Qt5_FOUND)
	message("Not building client - Qt5 is not found")
	return()
endif()

set(CMAKE_AUTOMOC ON)

add_subdirectory(apps)
add_subdirectory(qmlmodules)
