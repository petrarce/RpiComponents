#pragma once
#include <iostream>
#include <wiringPi.h>
#include <definitions.hpp>
#include <mutex>
#include <cmath>

class Servo
{
public:
	explicit Servo(int pin): pinNumber(pin)
	{
		pinMode(pinNumber, OUTPUT);

	}
	void rotate(float angle)
	{
		static std::mutex localMutex;
		std::lock_guard<std::mutex> guard(localMutex);
		pr_dbg("received angle:%f", angle);

		//map [-90,90]->[1000,2000]
		float impilsWidth = (-0.006 * std::min(90.f, std::max(-90.f, angle)) + 1.5f) * 1000;
		pr_dbg("impilsWidth:%f", impilsWidth);

		float fullDelay = 1000000.f / 50.f; //50MHz frequence (in microseconds)
		for(int i = 0; i < 10; i++){
			digitalWrite(pinNumber, 1);
			delayMicroseconds(impilsWidth);
			digitalWrite(pinNumber, 0);
			delayMicroseconds(fullDelay - impilsWidth);
		}
		pr_dbg("stop rotation");
	}

	Servo() = delete;
	Servo(const Servo&) = delete;
	const Servo& operator=(const Servo&) = delete;
private:
	int pinNumber {0};
};

class Machine {
	enum PINS {
		FOREWARD_PIN = 0,
		WHEEL = 2,
	};

public:
	explicit Machine() :
		servo(WHEEL)
	{
		pinMode(FOREWARD_PIN, OUTPUT);
		digitalWrite(FOREWARD_PIN, LOW);

	};
	void forevard()
	{
		digitalWrite(FOREWARD_PIN, 1);
	}
	void stop()
	{
		digitalWrite(FOREWARD_PIN, 0);
	}

	void rotate(float angle)
	{
		servo.rotate(angle);
	}

private:
	Servo servo;
};

