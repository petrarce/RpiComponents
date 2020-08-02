#pragma once

#include "Operator.hpp"

class Motor : public Operator<int8_t, float >
{
public:
	enum Direction {
		FOREWARD,
		STOP,
		BACKWARD,
	};
	explicit Motor(int pin);

private:
	void executionTask(int8_t dir, float speed) override;

	int pinNumber {0};
};
