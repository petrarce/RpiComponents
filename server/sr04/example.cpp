#include "SR04.hpp"

int main(int argc, char** argv)
{
	wiringPiSetup();
	SR04 sonar(4,5);
	while(1)
	{
		float dist = sonar.distance(std::stoi(argv[1]));
		fprintf(stderr, "distance: %f\n", dist);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}