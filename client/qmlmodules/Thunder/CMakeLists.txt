find_package(ZeroMQ QUIET)
if(NOT ZeroMQ_FOUND)
	return()
endif()

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
	COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${CMAKE_CURRENT_BINARY_DIR}
)
