#include <Operator.hpp>
#include <definitions.hpp>
#include <Singleton.hpp>
#include <boost/chrono.hpp>
#include <zmq.hpp>
#include "Environment.hpp"

class StatisticsOperator : public Operator<int /*period msec*/>
{
public:
	StatisticsOperator() = delete;
	StatisticsOperator(size_t port): 
		mPort(port),
		mContext(2),
		mSocket(mContext, zmq::socket_type::push)
	{
	}
private:
	zmq::context_t mContext;
	zmq::socket_t mSocket;
	int mPort;
	std::array<float, 360> distances;
	void executionTask(int period) override
	{
		assert(period > 0);
		mSocket.bind((std::string("tcp://*:") + std::to_string(mPort)).c_str());
		while(1)
		{
			auto wakeTime = boost::chrono::system_clock::now() + boost::chrono::milliseconds(period);
			//print environment stats
			for(int i = 0; i < 360; i++)
			{
				if((i%20) == 0)
					fprintf(stderr, "\n%d...%d: |", i, i+10);
				distances[i] = Singleton<Environment>::getInstance().distance(i);
				fprintf(stderr, "%2.1f, ", distances[i]);
			}
			mSocket.send(zmq::buffer(distances.data(), distances.size() * sizeof(distances[1])), zmq::send_flags::dontwait);
			boost::this_thread::sleep_until(wakeTime);
		}
	}
};