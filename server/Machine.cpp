#include "Machine.hpp"

Machine::Machine() :
	servo(WHEEL),
	motor(MOTOR), 
	rotationStation(RSTATION)
{
	rotationStation.run(1000, 180.f);
}

void Machine::forevard(float speed)
{
	motor.run(Motor::Direction::FOREWARD, speed);
}

void Machine::stop()
{
	motor.run(Motor::Direction::STOP, 0);
}

void Machine::rotate(float angle)
{
	servo.run(angle);
}

