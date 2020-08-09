//-------------------------------MPU6050 Accelerometer and Gyroscope C++ library-----------------------------
//Copyright (c) 2019, Alex Mous
//Licensed under the CC BY-NC SA 4.0

//Example code

#include "MPU6050.h"


int main() {
	MPU6050 device(0x68, 100);

	float ax, ay, az, gr, gp, gy; //Variables to store the accel, gyro and angle values
	sleep(1); //Wait for the MPU6050 to stabilize

/*
	//Calculate the offsets
	std::cout << "Calculating the offsets...\n    Please keep the accelerometer level and still\n    This could take a couple of minutes...";
	device.getOffsets(&ax, &ay, &az, &gr, &gp, &gy);
	std::cout << "Gyroscope R,P,Y: " << gr << "," << gp << "," << gy << "\nAccelerometer X,Y,Z: " << ax << "," << ay << "," << az << "\n";
*/

	//Read the current yaw angle
	device.calc_yaw = true;
	device.run();

	for (int i = 0; i < 40; i++) {
		device.getAngle(0, &gr);
		device.getAngle(1, &gp);
		device.getAngle(2, &gy);
		std::cout << "Current angle around the roll axis: " << gr << "\n";
		std::cout << "Current angle around the pitch axis: " << gp << "\n";
		std::cout << "Current angle around the yaw axis: " << gy << "\n";
		usleep(250000); //0.25sec
	}

	return 0;
}


