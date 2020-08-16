#include <definitions.hpp>
#include <wiringPi.h>
#include <chrono>
#include <thread>
#include <numeric>
#include <Operator.hpp>

class L298N
{
public:
	enum Direction {
		Clockwise,
		ConterClockwise,
	};

private:
	class PWM : public Operator<float /*frequence HZ*/>
	{
	public:
		explicit PWM(int pin): mPin(pin)
		{
			pinMode(mPin, OUTPUT);
		}
	private:
		void executionTask(float factor) override
		{
			assert(factor >= 0 && factor <= 1);
			//run on frequence 100HZ = 10 msec delay = 10000 microsec
			auto highDelay = boost::chrono::nanoseconds(static_cast<int>(100000 * factor));
			auto lowDelay = boost::chrono::nanoseconds(static_cast<int>(100000 * (1 - factor)));

			//interruption disabled
			boost::this_thread::disable_interruption dis;
			while(1)
			{
				digitalWrite(mPin, HIGH);
				boost::this_thread::sleep_for(highDelay);

				//restore interruption
				boost::this_thread::restore_interruption res(dis);
				digitalWrite(mPin, LOW);
				boost::this_thread::sleep_for(lowDelay);
				//res destroyed - interruptions disabled again
			}
		}

		int mPin;
	};
	void activate(L298N::Direction dir, float speedFactor, int pin1, int pin2, PWM& engine);
public:
	L298N() = delete;
	explicit L298N(	int in1, 
					int in2, 
					int in3, 
					int in4,
					int enableAPin,
					int enableBPin);

	void activateA(L298N::Direction dir, float speedFactor);
	void activateB(L298N::Direction dir, float speedFactor);
	void stopA();
	void stopB();

private:
	int mIn1Pin;
	int mIn2Pin;
	int mIn3Pin;
	int mIn4Pin;
	int mEnableAPin;
	int mEnableBPin;
	PWM engineA;
	PWM engineB;
};