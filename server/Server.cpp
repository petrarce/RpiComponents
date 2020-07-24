#include <zmq.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    zmq::context_t context{1};
    zmq::socket_t socket{context, zmq::socket_type::pair};

    string port = string(argv[1]);

    socket.bind("tcp://*:" + port);

    fprintf(stderr, "Starting server\n");
    while(1)
    {
        zmq::message_t msg;
        socket.recv(msg, zmq::recv_flags::none);
        fprintf(stderr, "received: %s\n", (msg.to_string() + "\0").c_str());
    }
    return 0;
}
