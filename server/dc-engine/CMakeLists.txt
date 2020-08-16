
add_library(dc-engine STATIC
	DC_ENG.cpp
	DC_ENG.hpp
)
target_link_libraries(dc-engine wiringPi)

add_executable(test-dc-engine
	example.cpp
)
target_link_libraries(test-dc-engine dc-engine wiringPi l298n i2c mpu6050 zmq boost_thread boost_chrono boost_system)