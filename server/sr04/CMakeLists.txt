
add_library(sr04 SHARED
	SR04.cpp
	SR04.hpp
)
target_link_libraries(sr04 wiringPi)

add_executable(test-sr04
	example.cpp
)
target_link_libraries(test-sr04 wiringPi)