#pragma once
#include <iostream>
#include <L298N.hpp>
#include "Servo.hpp"
#include "Motor.hpp"
#include "RotationStation.hpp"


class Machine {
	enum PINS {
		MOTORAIN1 = 0,
		MOTORAIN2 = 1,
		MOTORBIN1 = 2,
		MOTORBIN2 = 3,
		ENABLEA = 4,
		ENABLEB = 5,
	};

public:
	explicit Machine():
		l298n(		MOTORAIN1,
					MOTORAIN2,
					MOTORBIN1,
					MOTORBIN2,
					ENABLEA,
					ENABLEB)
	{

	}
	void forevard()
	{
		l298n.activateA(L298N::Direction::Clockwise);
		l298n.activateB(L298N::Direction::Clockwise);

	}
	void backvard()
	{
		l298n.activateA(L298N::Direction::ConterClockwise);
		l298n.activateB(L298N::Direction::ConterClockwise);
	}
	void stop()
	{
		l298n.stopA();
		l298n.stopB();
	}
	void rotate_left()
	{
		l298n.activateA(L298N::Direction::Clockwise);
		l298n.activateB(L298N::Direction::ConterClockwise);
	}
	void rotate_right()
	{
		l298n.activateA(L298N::Direction::ConterClockwise);
		l298n.activateB(L298N::Direction::Clockwise);
	}

private:
	L298N l298n;

};

