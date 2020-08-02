
add_library(mpu6050 SHARED
	MPU6050.cpp
	MPU6050.h
)

add_executable(example
	Example.cpp
)
target_link_libraries(example mpu6050 i2c pthread boost_thread boost_system boost_chrono)