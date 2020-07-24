# static library
add_executable(server
    Server.cpp
    Server.hpp
)
# install libs
install(TARGETS server DESTINATION bin/)
target_link_libraries(server zmq)
