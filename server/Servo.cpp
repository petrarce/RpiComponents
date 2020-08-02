#include "Servo.hpp"
#include <boost/thread/thread.hpp>
#include <wiringPi.h>
#include <cmath>


Servo::Servo(int pin): pinNumber(pin)
{
	pinMode(pinNumber, OUTPUT);

}

void Servo::executionTask(float angle)
{
	//map [-90,90]->[1000,2000]
	boost::this_thread::interruption_point();
	float impilsWidth = (-0.006 * std::min(90.f, std::max(-90.f, angle)) + 1.5f) * 1000;
	for(int i = 0; i < 10; i++){
		boost::this_thread::interruption_point();
		digitalWrite(pinNumber, 1);
		delayMicroseconds(impilsWidth);
		boost::this_thread::interruption_point();
		digitalWrite(pinNumber, 0);
		delayMicroseconds(impilsWidth);
		boost::this_thread::interruption_point();
	}
}

