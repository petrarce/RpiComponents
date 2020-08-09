#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
extern "C" {
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
}
#include <cmath>
#include <thread>
#include <Operator.hpp>

#define _POSIX_C_SOURCE 200809L //Used for calculating time

#define TAU 0.05 //Complementary filter percentage
#define RAD_T_DEG 57.29577951308 //Radians to degrees (180/PI)


class MPU6050 : public Operator<> {
	public:
		enum GyroRange {
			GyroRange250 = 0,
			GyroRange500 = 1,
			GyroRange1000 = 2,
			GyroRange2000 = 3,
		};
		enum AccelRange {
			AccelRange2 = 0,
			AccelRange4 = 1,
			AccelRange8 = 2,
			AccelRange16 = 3,
		};


		MPU6050(int8_t addr, 
				size_t period = 500, 
				GyroRange gyro_range = GyroRange250, 
				AccelRange accel_range = AccelRange2);
		void getAccelRaw(float *x, float *y, float *z);
		void getGyroRaw(float *roll, float *pitch, float *yaw);
		void getAccel(float *x, float *y, float *z);
		void getGyro(float *roll, float *pitch, float *yaw);
		void getOffsets(float *ax_off, float *ay_off, float *az_off, float *gr_off, float *gp_off, float *gy_off);
		int getAngle(int axis, float *result);
		size_t pollPeriod {500};
		bool calc_yaw;

	private:
		void executionTask() override;
		void _update();
		void calibrateGyro();
		void calibrateAccel();
		void calibrate(std::array<float, 3>& offsets, void (MPU6050::*fn)(float*, float*, float*));

		std::array<float, 3> _accel_offsets {0, 0, 0};
		std::array<float, 3> _accel_angle;

		std::array<float, 3> _gyro_offsets {0, 0, 0};
		std::array<float, 3> _gyro_angle;
		
		std::array<float, 3> _angle; //Store all angles (accel roll, accel pitch, accel yaw, gyro roll, gyro pitch, gyro yaw, comb roll, comb pitch comb yaw)

		float ax, ay, az, gr, gp, gy; //Temporary storage variables used in _update()

		int MPU6050_addr;
		int f_dev; //Device file

		float dt; //Loop time (recalculated with each loop)

		struct timespec start,end; //Create a time structure

		bool _first_run = 1; //Variable for whether to set gyro angle to acceleration angle in compFilter

		constexpr static std::array<float, 4> _gyro_sens {131.f, 65.5f, 32.8f, 16.4f};
		constexpr static std::array<float, 4> _accel_sens {16384.f, 8192.f, 4096.f, 2048.f};
		GyroRange _gyro_range;
		AccelRange _accel_range;



};
