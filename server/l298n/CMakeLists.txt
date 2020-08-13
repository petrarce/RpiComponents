
add_library(l298n SHARED
	L298N.cpp
	L298N.hpp
)
target_link_libraries(l298n wiringPi)

add_executable(test-l298n
	example.cpp
)
target_link_libraries(test-l298n wiringPi l298n boost_thread boost_system boost_chrono)