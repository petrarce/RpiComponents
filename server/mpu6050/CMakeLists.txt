
add_library(mpu6050 SHARED
	MPU6050.cpp
	MPU6050.h
)

add_executable(test-mpu6050
	Example.cpp
)
target_link_libraries(test-mpu6050 mpu6050 i2c pthread boost_thread boost_system boost_chrono)

add_executable(test2-mpu6050
	Example2.cpp
)
target_link_libraries(test2-mpu6050 mpu6050 i2c pthread boost_thread boost_system boost_chrono)