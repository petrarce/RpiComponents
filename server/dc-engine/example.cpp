#include <zmq.hpp>
#include "DC_ENG.hpp"

int main(int argc, char** argv)
{
	// zmq::context_t context(0);
	// zmq::socket_t socket(context, zmq::socket_type::pair);
	// socket.bind(std::string("tcp://*:") + std::string(argv[1]));
	
	DC_ENG engine;
	engine.run(120);
	engine.configurePid(std::stof(argv[1]), std::stof(argv[2]), std::stof(argv[3]));
	
	std::string line;
	while(std::getline(std::cin, line, '\n'))
	{
		// zmq::message_t msg;
		// socket.recv(msg, zmq::recv_flags::none);
		// Messages type = *static_cast<Messages*>(msg.data());
		// float value = *static_cast<float*>(msg.data() + sizeof(Messages));
		engine.goTo(std::stof(line));
	}
	return 0;
}