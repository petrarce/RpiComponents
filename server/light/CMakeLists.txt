
add_library(lightDiod STATIC
	Light.hpp
	Light.cpp
)
target_link_libraries(lightDiod wiringPi)

add_executable(test-lightDiod
	example.cpp
)
target_link_libraries(test-lightDiod wiringPi lightDiod)