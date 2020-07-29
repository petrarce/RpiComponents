
find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)
if (WIRINGPI_LIBRARIES MATCHES ".*-NOTFOUND")
	message("Not building server: wiringPi not found")
	return()
endif()

find_package(Boost COMPONENTS thread system QUIET)
if(NOT Boost_FOUND)
    message("Not building server: Boost not found")
    return()
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(server
    Hardware.cpp
	Hardware.hpp
    Server.cpp
    Server.hpp
)
# install libs
install(TARGETS server DESTINATION bin/)
target_link_libraries(server zmq wiringPi boost_thread boost_system)
