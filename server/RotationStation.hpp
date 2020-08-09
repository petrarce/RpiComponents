#pragma once
#include <definitions.hpp>
#include <Operator.hpp>
#include <MPU6050.h>
#include "Servo.hpp"

class RotationStation : public Operator<int /*speed milliseconds*/, float /*rotation angle*/>
{
public:
	RotationStation() = delete;
	explicit RotationStation(int srvPin);

private:
	void executionTask(int period, float sectorWidth) override;


	Servo mServo;
	MPU6050 mMpuDevice;
};