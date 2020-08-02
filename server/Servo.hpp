#pragma once
#include "Operator.hpp"

class Servo : public Operator<float>
{
	
public:
	explicit Servo(int pin);

private:
	void executionTask(float angle) override;

	int pinNumber {0};
};
