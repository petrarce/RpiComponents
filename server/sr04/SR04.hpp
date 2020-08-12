#include <wiringPi.h>
#include <chrono>
#include <thread>

class SR04
{
public:
	SR04() = delete;
	explicit SR04(int trigger, int echo):
		mEcho(echo),
		mTrigger(trigger)
	{
		pinMode(mTrigger, OUTPUT);
		pinMode(mEcho, INPUT);
	}
	float distance(float maxDist /*santimeters*/)
	{

		int timeoutMsec = maxDist * 36;
		
		digitalWrite(mTrigger, HIGH);
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		digitalWrite(mTrigger, LOW);
		
		auto begin = std::chrono::system_clock::now();
		while(digitalRead(mEcho) == LOW)
		{
				if(timeoutMsec < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin).count())
				{
					return maxDist;
				}
		}  

		auto start = std::chrono::system_clock::now();
		while(digitalRead(mEcho) == HIGH 
				|| timeoutMsec < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count()){}
		auto end = std::chrono::system_clock::now();
		int duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		return 360.f / 2.f * duration / 10000.f;
	}
private:
	int mEcho;
	int mTrigger;
};