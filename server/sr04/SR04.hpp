#include <definitions.hpp>
#include <wiringPi.h>
#include <chrono>
#include <thread>
#include <numeric>

class SR04
{
public:
	SR04() = delete;
	explicit SR04(int trigger, int echo);
	float distance(float maxDist);
private:
	int mEcho;
	int mTrigger;
};