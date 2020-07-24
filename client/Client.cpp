#include <iostream>
#include <zmq.hpp>
using namespace std;
int main(int argc, char** argv)
{
    zmq::context_t context{1};
    zmq::socket_t socket{context, zmq::socket_type::pair};

    string addr = string(argv[1]);
    string port = string(argv[2]);
    socket.connect("tcp://" + addr + ":" + port);


    socket.send(zmq::buffer(string(argv[3])), zmq::send_flags::none);
    return 0;
}
