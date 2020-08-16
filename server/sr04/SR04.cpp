#include "SR04.hpp"

SR04::SR04(int trigger, int echo):
	mEcho(echo),
	mTrigger(trigger)
{
	pinMode(mTrigger, OUTPUT);
	pinMode(mEcho, INPUT);
}
float SR04::distance(float maxDist /*santimeters*/)
{

	constexpr float multiplier = 2.f / 360.f * 10000.f;
	int timeoutMicrosec = maxDist * multiplier;
	
	digitalWrite(mTrigger, HIGH);
	std::this_thread::sleep_for(std::chrono::microseconds(10));
	digitalWrite(mTrigger, LOW);
	
	//busy wait
	auto begin = std::chrono::system_clock::now();
	while(digitalRead(mEcho) == LOW)
	{
		int delayPeriod = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - begin).count();
		//TODO: Calibrate sonar for minimal delay
		if(delayPeriod > 1000)
			return -1;//timeout - return -1 as failure code 
	}

	auto start = std::chrono::system_clock::now();
	while(digitalRead(mEcho) == HIGH)
	{
		auto timeNow = std::chrono::system_clock::now();
		int delayPeriod = std::chrono::duration_cast<std::chrono::microseconds>(timeNow - start).count();
		if(delayPeriod > timeoutMicrosec)
		{
			break; //break on maximum distance expired
		}
	}
	auto end = std::chrono::system_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	return 360.f / 2.f * duration / 10000.f;
}
