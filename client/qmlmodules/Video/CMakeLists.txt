find_package(GStreamer REQUIRED)
find_package(GLIB REQUIRED)
find_package(GObject REQUIRED)

add_library(video-plugin SHARED
	GstreamerPipelineRunner.cpp
	GstreamerPipelineRunner.h
	VideoDevicesPoll.cpp
	VideoDevicesPoll.h
	VideoPlugin.cpp
	VideoPlugin.h
)
target_include_directories(video-plugin PRIVATE ${GSTREAMER_INCLUDE_DIR} ${GLIB_INCLUDE_DIRS})
target_link_libraries(video-plugin 
	Qt5::Core 
	Qt5::Qml 
	gstreamer-1.0
)
add_custom_command(TARGET video-plugin POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${CMAKE_CURRENT_BINARY_DIR}
)
