#pragma once
#include <iostream>
#include "Servo.hpp"
#include "Motor.hpp"



class Machine {
	enum PINS {
		MOTOR = 0,
		WHEEL = 2,
	};

public:
	explicit Machine() :
		servo(WHEEL),
		motor(MOTOR){};
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
};

