#pragma once
#include <iostream>
#include <wiringPi.h>
#include <definitions.hpp>
#include <mutex>
#include <cmath>
#include <boost/thread/thread.hpp>

template<class ... Args>
class Operator
{
	std::unique_ptr<boost::thread> task;
	virtual void executionTask(Args... args) = 0;
	std::function<void (Args...)> fn;
public:
	Operator()
	{
		fn = [this](Args... args)
		{ 
			static std::mutex localMutex;
			std::lock_guard<std::mutex> guard(localMutex);
			try 
			{
				this->executionTask(args...);
			}
			catch(const boost::thread_interrupted& inter)
			{
				pr_dbg("thread interrupted");
			}	
		};
	}
	void run(Args... args)
	{
		if(task)
		{
			task->interrupt();
			task->join();
		}
		task = std::unique_ptr<boost::thread>(new boost::thread(fn, args...));
	}

	Operator(const Operator&) = delete;
	const Operator& operator=(const Operator&) = delete;

};

class Servo : public Operator<float>
{
	void executionTask(float angle) override
	{
		//map [-90,90]->[1000,2000]
		boost::this_thread::interruption_point();
		float impilsWidth = (-0.006 * std::min(90.f, std::max(-90.f, angle)) + 1.5f) * 1000;
		for(int i = 0; i < 10; i++){
			boost::this_thread::interruption_point();
			digitalWrite(pinNumber, 1);
			delayMicroseconds(impilsWidth);
			boost::this_thread::interruption_point();
			digitalWrite(pinNumber, 0);
			delayMicroseconds(impilsWidth);
			boost::this_thread::interruption_point();
		}
	}

public:
	explicit Servo(int pin): pinNumber(pin)
	{
		pinMode(pinNumber, OUTPUT);

	}

private:
	int pinNumber {0};
};
class Motor : public Operator<int8_t, float >
{
public:
	enum Direction {
		FOREWARD,
		STOP,
		BACKWARD,
	};

	explicit Motor(int pin): pinNumber(pin)
	{
		pinMode(pinNumber, OUTPUT);
	}
private:
	void executionTask(int8_t dir, float speed) override
	{
		boost::this_thread::interruption_point();
		switch(dir)
		{
			case Direction::FOREWARD:
			digitalWrite(pinNumber, 1);
			break;
			case Direction::STOP:
			digitalWrite(pinNumber, 1);
			break;
			case Direction::BACKWARD:
			pr_warn("Unsupported movement direction");
			break;
			default:
			pr_warn("unknown direction - ignoring");
			break;
		}
	}

	int pinNumber {0};
};

class Machine {
	enum PINS {
		MOTOR = 0,
		WHEEL = 2,
	};

public:
	explicit Machine() :
		servo(WHEEL),
		motor(MOTOR){};
	void forevard(float speed)
	{
		motor.run(Motor::Direction::FOREWARD, speed);
	}
	void stop()
	{
		motor.run(Motor::Direction::STOP, 0);
	}

	void rotate(float angle)
	{
		servo.run(angle);
	}

private:
	Servo servo;
	Motor motor;
};

