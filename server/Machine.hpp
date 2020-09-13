#pragma once
#include <iostream>
#include <L298N.hpp>
#include <Light.hpp>
#include "Motor.hpp"


class Machine {
	enum PINS {
		MOTORAIN1 = 24,
		MOTORAIN2 = 25,
		MOTORBIN1 = 28,
		MOTORBIN2 = 29,
		ENABLEA = 23,
		ENABLEB = 27,
		DIOD = 0
	};

public:
	explicit Machine():
		l298n(		MOTORAIN1,
					MOTORAIN2,
					MOTORBIN1,
					MOTORBIN2,
					ENABLEA,
					ENABLEB),
		diod(DIOD)
	{}

	void forevard()
	{
		l298n.activateA(L298N::Direction::Clockwise);
		l298n.activateB(L298N::Direction::Clockwise);
		diod.turnOn();

	}

	void backvard()
	{
		l298n.activateA(L298N::Direction::ConterClockwise);
		l298n.activateB(L298N::Direction::ConterClockwise);
		diod.turnOn();

	}

	void stop()
	{
		l298n.stopA();
		l298n.stopB();
		diod.turnOff();

	}

	void rotate_left()
	{
		l298n.activateA(L298N::Direction::ConterClockwise);
		l298n.activateB(L298N::Direction::Clockwise);
		diod.turnOn();
	}

	void rotate_right()
	{
		l298n.activateA(L298N::Direction::Clockwise);
		l298n.activateB(L298N::Direction::ConterClockwise);
		diod.turnOn();
	}

private:
	L298N l298n;
	LightDiod diod;
	

};

