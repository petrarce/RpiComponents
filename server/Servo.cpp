#include "Servo.hpp"
#include <boost/thread/thread.hpp>
#include <wiringPi.h>
#include <cmath>


Servo::Servo(int pin): pinNumber(pin)
{
	pinMode(pinNumber, OUTPUT);
	rotate(0);

}
void Servo::rotate(float angle)
{
	float impilsWidth = (-0.006 * std::min(90.f, std::max(-90.f, angle)) + 1.5f) * 1000;
	int loops = 0;
	float delta = angle - currentAngle;
	if(std::fabs(delta) > 70)
		loops = 10;
	else if (std::fabs(delta) > 50)
		loops = 8;
	else if (std::fabs(delta) > 30)
		loops = 4;
	else if (std::fabs(delta) > 0)
		loops = 2;
	float stepDelta = delta / loops;
	for(int i = 0; i < loops; i++){
		auto tp1 = boost::chrono::system_clock::now() + boost::chrono::microseconds(static_cast<int>(impilsWidth));
		auto tp2 = boost::chrono::system_clock::now() + boost::chrono::microseconds(static_cast<int>(impilsWidth * 2));
		digitalWrite(pinNumber, 1);
		boost::this_thread::sleep_until(tp1);
		digitalWrite(pinNumber, 0);
		boost::this_thread::sleep_until(tp2);
		currentAngle += stepDelta;
	}
	digitalWrite(pinNumber, 0);
}

void Servo::executionTask(float angle)
{
	//map [-90,90]->[1000,2000]
	boost::this_thread::interruption_point();
	rotate(angle);
}

