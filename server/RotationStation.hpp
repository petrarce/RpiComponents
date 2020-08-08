#pragma once
#include <wiringPi.h>
#include <definitions.hpp>
#include <Operator.hpp>
#include <cassert>
#include <MPU6050.h>
#include "Servo.hpp"

class RotationStation : public Operator<int /*speed milliseconds*/, float /*rotation angle*/>
{
public:
	RotationStation() = delete;
	RotationStation(int srvPin): 
		mServo(srvPin),
		mMpuDevice(0x68, 100)
	{
		mMpuDevice.calc_yaw = true;
		mMpuDevice.run();
	}



private:
	void executionTask(int period, float sectorWidth) override
	{

		assert(period >= 1 && sectorWidth >= 1);
		float angle = 0;
		int delta = 1;
		for(;;)
		{

			float yaw = 0;
			mMpuDevice.getAngle(2, &yaw);
			pr_dbg("angleZ:%f", yaw);

			auto delay = boost::chrono::system_clock::now() + 
							boost::chrono::milliseconds(static_cast<int>(period / sectorWidth));
			boost::this_thread::interruption_point();
			mServo.rotate(angle);
			boost::this_thread::interruption_point();
			if(std::fabs(std::fabs(angle) - sectorWidth/2) < 1.f)
				delta *= -1;
			angle += delta;

			boost::this_thread::sleep_until(delay);
		}
	}


	Servo mServo;
	MPU6050 mMpuDevice;
};