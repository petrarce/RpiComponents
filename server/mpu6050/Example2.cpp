#include <definitions.hpp>
#include <chrono>
#include <thread>
#include "MPU6050.h"


int main() {



	MPU6050 device(0x68, 100, MPU6050::GyroRange::GyroRange250);

	float angleX = 0, angleY = 0, angleZ = 0;
	for (;;) {
		float gx, gy, gz;
		auto wake_point = std::chrono::system_clock::now() + std::chrono::milliseconds(10);
		device.getGyro(&gx, &gy, &gz);
		pr_dbg("gx:\t%0.3f\tgy:\t%0.3f\tgz:\t%0.3f", gx, gy, gz);
		std::this_thread::sleep_until(wake_point); //0.25sec
	}


	return 0;
}


