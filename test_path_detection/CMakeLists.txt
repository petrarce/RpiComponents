find_package(Qt5 COMPONENTS Core Qml Quick Gui Quick QUIET)
if (NOT Qt5_FOUND)
	message("Not building client - Qt5 is not found")
	return()
endif()

set(CMAKE_AUTOMOC ON)


add_library(path-exploration SHARED
    Robot.cpp
    Robot.hpp
    PathExploration.cpp
    PathExploration.hpp
    Environment.cpp
    Environment.hpp
)
target_link_libraries(path-exploration Qt5::Core Qt5::Qml Qt5::Gui Qt5::Quick boost_thread boost_system)

add_custom_command(TARGET path-exploration POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/PathExploration
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libpath-exploration.so
                                        ${CMAKE_CURRENT_SOURCE_DIR}/qmldir
                                        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/PathExploration
)
