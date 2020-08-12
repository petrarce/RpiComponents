#pragma once
#include <definitions.hpp>
#include <Operator.hpp>
#include <MPU6050.h>
#include <SR04.hpp>
#include "Servo.hpp"
#include "DistanceSensor.hpp"


class RotationStation : public Operator<int /*speed milliseconds*/, float /*rotation angle*/>
{
public:
	RotationStation() = delete;
	explicit RotationStation(int srvPin, int echoPin, int trigPin, float maxDist = 50.f);

private:
	void executionTask(int period, float sectorWidth) override;

	Servo mServo;
	MPU6050 mMpuDevice;
	SR04 mSonar;
	float mMaxDist;
};