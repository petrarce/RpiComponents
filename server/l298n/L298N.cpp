#include "L298N.hpp"

L298N::L298N(	int in1, 
				int in2, 
				int in3, 
				int in4,
				int enableAPin,
				int enableBPin):
	mIn1Pin(in1),
	mIn2Pin(in2),
	mIn3Pin(in3),
	mIn4Pin(in4),
	engineA(enableAPin),
	engineB(enableBPin)
{
	pinMode(mIn1Pin, OUTPUT);
	pinMode(mIn2Pin, OUTPUT);
	pinMode(mIn3Pin, OUTPUT);
	pinMode(mIn4Pin, OUTPUT);
}

void L298N::activateA(L298N::Direction dir, float speedFactor)
{
	activate(dir, speedFactor, mIn1Pin, mIn2Pin, engineA);
}
void L298N::activateB(L298N::Direction dir, float speedFactor)
{
	activate(dir, speedFactor, mIn3Pin, mIn4Pin, engineB);
}
void L298N::activate(L298N::Direction dir, float speedFactor, int pin1, int pin2, PWM& engine)
{
	switch(dir)
	{
		case L298N::Direction::Clockwise:
		digitalWrite(pin1, HIGH);
		digitalWrite(pin2, LOW);
		break;

		case L298N::Direction::ConterClockwise:
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, HIGH);
		break;

		default:
		assert(0);
	}
	engine.run(speedFactor);
}
void L298N::stopA()
{
	digitalWrite(mIn1Pin, LOW);
	digitalWrite(mIn2Pin, LOW);
	engineA.stop();
}
void L298N::stopB()
{
	digitalWrite(mIn3Pin, LOW);
	digitalWrite(mIn4Pin, LOW);
	engineB.stop();
}

