# static library
find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)
if (WIRINGPI_LIBRARIES MATCHES ".*-NOTFOUND")
	message("Not building server: wiringPi not found")
	return()
endif()
add_executable(server
    Hardware.cpp
	Hardware.hpp
    Server.cpp
    Server.hpp
)
# install libs
install(TARGETS server DESTINATION bin/)
target_link_libraries(server zmq wiringPi)
