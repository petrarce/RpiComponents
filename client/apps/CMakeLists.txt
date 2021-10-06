add_executable(qmlloader
	QmlLoader.cpp
)
target_link_libraries(qmlloader Qt5::Core Qt5::Qml Qt5::Quick Qt5::Gui)
