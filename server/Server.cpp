#include <iostream>
#include <zmq.hpp>
#include <definitions.hpp>
#include <wiringPi.h>
#include "Machine.hpp"
#include "RotationStation.hpp"
#include "StatisticsOperator.hpp"

using namespace std;

int main(int argc, char** argv)
{
    //set up wiring pi
    wiringPiSetup();

    //set up zeromq tcp connection
    string port = string(argv[1]);
    zmq::context_t context{1};
    zmq::socket_t socket{context, zmq::socket_type::pair};
    socket.bind("tcp://*:" + port);

    //TODO:
    /*
        create thread, that receives commands and starts manipulations ofon the car/copter/tank...
        create thread which listens requests and replyes data on the requests
    */
    //init logic
    Machine machine;
    // StatisticsOperator stats(stoi(port) + 1);
    // stats.run(10000);

    //start listening loop
    //message format: 
        //1-st byte - action
        //2-nd byte - value
    fprintf(stderr, "Starting server\n");
    int msgNum = 0;
    while(1)
    {
        zmq::message_t msg;
        socket.recv(msg, zmq::recv_flags::none);
        
        if(msg.size() < 2)
        {
            pr_warn("invalide message format received: 2 bytes expected");
            continue;
        }
        int8_t* data = static_cast<int8_t*>(msg.data());
        int dataSize = msg.size();

        // if(msgNum > data[2] && msgNum - data[2] < 50 || data[2] > msgNum && data[2] - msgNum > 50)
        //     continue;

        pr_dbg("Received action: %d, received value: %d, message num: %d", data[0], data[1], data[2]);
        msgNum = data[2];
        switch(data[0])
        {
            case Forevard:
                machine.forevard();
                break;
            case Backward:
                machine.backvard();
                break;
            case Stop:
                machine.stop();
                break;
            case RotateLeft:
                machine.rotate_left();
                break;
            case RotateRight:
                machine.rotate_right();
                break;
            case Error:
                pr_warn("Some error from client... just ignore)))");
                break;
            default: 
                pr_err("unknown message from client, ignoring...");
                break;
        }
    }
    return 0;
}
