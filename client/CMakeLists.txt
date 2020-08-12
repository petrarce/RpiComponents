find_package(Qt5 COMPONENTS Core Qml Quick Gui QUIET)
if (NOT Qt5_FOUND)
	message("Not building client - Qt5 is not found")
	return()
endif()

set(CMAKE_AUTOMOC ON)

add_executable(client
    Client.cpp
    Client.hpp
)
target_link_libraries(client zmq)

add_library(thunder-plugin SHARED
    ThunderDistanceListener.cpp
    ThunderDistanceListener.hpp
    ThunderListener.cpp
    ThunderListener.hpp
    ThunderPlugin.cpp
    ThunderPlugin.hpp
    RpiConnector.cpp
    RpiConnector.hpp
)
target_link_libraries(thunder-plugin Qt5::Core Qt5::Qml zmq)

add_custom_command(TARGET thunder-plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Thunder
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libthunder-plugin.so ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Thunder
)

add_executable(qmlloader
    QmlLoader.cpp
)
target_link_libraries(qmlloader Qt5::Core Qt5::Qml Qt5::Quick Qt5::Gui)
