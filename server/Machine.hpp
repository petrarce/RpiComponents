#pragma once
#include <iostream>
#include "Servo.hpp"
#include "Motor.hpp"
#include "RotationStation.hpp"


class Machine {
	enum PINS {
		MOTOR = 0,
		WHEEL = 2,
		RSTATION = 3
	};

public:
	explicit Machine() :
		servo(WHEEL),
		motor(MOTOR), 
		rotationStation(RSTATION)
		{
			rotationStation.run(1000, 180.f);
		};
	void forevard(float speed)
	{
		motor.run(Motor::Direction::FOREWARD, speed);
	}
	void stop()
	{
		motor.run(Motor::Direction::STOP, 0);
	}

	void rotate(float angle)
	{
		servo.run(angle);
	}

private:
	Servo servo;
	Motor motor;
	RotationStation rotationStation;

};

