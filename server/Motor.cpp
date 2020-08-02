#include "Motor.hpp"
#include <boost/thread/thread.hpp>
#include <wiringPi.h>


Motor::Motor(int pin): pinNumber(pin)
{
	pinMode(pinNumber, OUTPUT);
}
void Motor::executionTask(int8_t dir, float speed)
{
	boost::this_thread::interruption_point();
	switch(dir)
	{
		case Direction::FOREWARD:
		digitalWrite(pinNumber, 1);
		break;
		case Direction::STOP:
		digitalWrite(pinNumber, 1);
		break;
		case Direction::BACKWARD:
		pr_warn("Unsupported movement direction");
		break;
		default:
		pr_warn("unknown direction - ignoring");
		break;
	}
}
