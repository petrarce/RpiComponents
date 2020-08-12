#pragma once
#include <iostream>
#include <random>
class DistanceSensor
{
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<float> distr;
public:
	DistanceSensor() = delete;
	explicit DistanceSensor(int echoPin, int triggerPin):
		gen(rd()),
		distr(0, 20.f){}
	DistanceSensor(const DistanceSensor& other) = delete;
	float getDistance()
	{
		return distr(gen);
	}
};