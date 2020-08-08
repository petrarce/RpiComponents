#pragma once
#include <Operator.hpp>

class Servo : public Operator<float>
{
	
public:
	explicit Servo(int pin);
	void rotate(float angle);

private:
	void executionTask(float angle) override;
	float currentAngle {0};
	int pinNumber {0};
};
