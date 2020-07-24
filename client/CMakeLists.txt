# static library
add_executable(client
    Client.cpp
    Client.hpp
)
# install libs
install(TARGETS client DESTINATION bin/)
target_link_libraries(client zmq)
