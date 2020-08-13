
find_library(wiringPi_LIB NAMES wiringPi REQUIRED)
find_library(i2c_LIB i2c REQUIRED)

if (i2c_LIB MATCHES ".*-NOTFOUND")
	message("Not building server: i2c not found")
	return()
endif()
if (wiringPi_LIB MATCHES ".*-NOTFOUND")
	message("Not building server: wiringPi not found")
	return()
endif()

find_package(Boost COMPONENTS thread system chrono QUIET)
if(NOT Boost_FOUND)
    message("Not building server: Boost not found")
    return()
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(server
	Machine.cpp
	Machine.hpp
	Motor.cpp
	Motor.hpp
	Server.cpp
	Servo.cpp
	Servo.hpp
	RotationStation.cpp
	RotationStation.hpp
)
# install libs
install(TARGETS server DESTINATION bin/)
target_link_libraries(server 
	zmq 
	wiringPi 
	i2c 
	boost_thread 
	boost_system 
	boost_chrono 
	mpu6050 
	sr04)

include_directories(AFTER ./mpu6050/)
include_directories(AFTER ./sr04/)
include_directories(AFTER ./l298n/)

add_subdirectory(./mpu6050/)
add_subdirectory(./sr04/)
add_subdirectory(./l298n/)
