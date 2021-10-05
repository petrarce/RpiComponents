
add_library(video-plugin SHARED
    VideoDevicesPoll.h
    VideoPlugin.cpp
    VideoPlugin.h
    VideoDevicesPoll.cpp
)
target_link_libraries(video-plugin Qt5::Core Qt5::Qml)
add_custom_command(TARGET video-plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${CMAKE_CURRENT_BINARY_DIR}
)
