#include <wiringPi.h>
#include <cassert>
#include <Singleton.hpp>
#include "RotationStation.hpp"
#include "Environment.hpp"

RotationStation::RotationStation(int srvPin, int echoPin, int trigPin): 
	mServo(srvPin),
	mDistSens(echoPin, trigPin),
	mMpuDevice(0x68, 100)
{
	mMpuDevice.calc_yaw = true;
	mMpuDevice.run();
}



void RotationStation::executionTask(int period, float sectorWidth)
{

	assert(period >= 1 && sectorWidth >= 1);
	float angle = 0;
	int delta = 1;
	for(;;)
	{

		//read yaw angle
		float yaw = 0;
		mMpuDevice.getAngle(2, &yaw);
		auto delay = boost::chrono::system_clock::now() + 
						boost::chrono::milliseconds(static_cast<int>(period / sectorWidth));

		//read distance value
        float dist = mDistSens.getDistance();
        Singleton<Environment>::getInstance().setDistance(yaw, dist);

		//rotate servo
		boost::this_thread::interruption_point();
		mServo.rotate(angle);
		boost::this_thread::interruption_point();

		if(std::fabs(std::fabs(angle) - sectorWidth/2) < 1.f)
			delta *= -1;
		angle += delta;

		boost::this_thread::sleep_until(delay);
	}
}
