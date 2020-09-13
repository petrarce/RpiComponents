#include <wiringPi.h>

class LightDiod
{
public:
	LightDiod() = delete;
	LightDiod(int pin):
		mPin(pin)
	{
		pinMode(mPin, OUTPUT);
	}

	void turnOn(){digitalWrite(mPin, HIGH);}
	void turnOff(){digitalWrite(mPin, LOW);}
private:
	int mPin;
};