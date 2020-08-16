#pragma once
#include <iostream>
#include <cassert>
#include <thread>

class Environment
{
private:
	std::mutex distMutex;
	std::array<float, 360> distances;

public:
	Environment() = default;
	float distance(int angle) const
	{
		assert(angle >= 0 && angle < 360);
		return distances[angle];
	}
	
	void setDistance(float angle, float val)
	{
		float v1 = angle/360.f;
		float v2 = (1 - 2 * std::signbit(angle)) * std::floor(std::fabs(angle / 360.f));
		angle = (v1 - v2) * 360.f;
		if(std::fabs(angle) >= 180)
		{
			angle = (1 - 2 * std::signbit(angle)) * 360 - angle;
		}
		angle += 180;
		assert(angle >= 0 && angle < 360);

		std::lock_guard<std::mutex> guard(distMutex);
		distances[static_cast<int>(std::floor(angle))] = val;
	}
};