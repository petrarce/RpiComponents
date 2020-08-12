#pragma once
#include <iostream>
#include "Servo.hpp"
#include "Motor.hpp"
#include "RotationStation.hpp"


class Machine {
	enum PINS {
		MOTOR = 0,
		WHEEL = 2,
		RSTATION = 3,
		DISTECHO = -1,
		DISTTRIGGER = -1,
	};

public:
	explicit Machine();
	void forevard(float speed);
	void stop();
	void rotate(float angle);

private:
	Servo servo;
	Motor motor;
	RotationStation rotationStation;

};

